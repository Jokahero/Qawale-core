#include "HardAI.hpp"

#include <QtConcurrent/QtConcurrent>

namespace QAwale {
    namespace Core {
        HardAI::HardAI(int number, const QString &name) : AI(number, name) {}

        int HardAI::play(const Gameboard &state) {
            int max = -1000;
            int position = _lastHoleNumber;

            QMap<int, QFuture<int> > threads;
            for (unsigned int i = _firstHoleNumber; i <= _lastHoleNumber; ++i) {
                if (state.getHoleSeedCount(i) > 0) {
                    Gameboard finalState;
                    int taking = state.simulate(i, finalState);
                    TAlphaBeta alphaBeta;
                    alphaBeta.alpha = -100;
                    alphaBeta.beta = 500;
                    QFuture<int> thread = QtConcurrent::run<int>(this, &HardAI::min, finalState, DEPTH, taking, 0, alphaBeta);
                    threads.insert(i, thread);
                }
            }

            QMapIterator<int, QFuture<int> > iterator (threads);
            while (iterator.hasNext()) {
                iterator.next();
                if (iterator.value().result() > max) {
                    max = iterator.value().result();
                    position = iterator.key();
                }
            }

            return position;
        }

        int HardAI::min(Gameboard state, unsigned int depth, unsigned int playerTaking, unsigned int opponentTaking, TAlphaBeta alphaBeta) const {
            if (depth == 0)
                return evaluate(state, playerTaking, opponentTaking, _number);
            else {
                int min = 500;
                unsigned int emptyHoleCount = 0;
                int tmp;

                for (unsigned int i = _firstHoleNumber; i <= _lastHoleNumber; ++i) {
                    if (state.getHoleSeedCount(i) > 0) {
                        Gameboard finalState = state;
                        int taking = state.simulate(i, finalState);

                        tmp = max(finalState, depth - 1, playerTaking, opponentTaking + taking, alphaBeta);

                        if (alphaBeta.alpha >= tmp)	// Coupure α
                            return tmp;

                        if (tmp < min)
                            min = tmp;

                        if (tmp < alphaBeta.beta)
                            alphaBeta.beta = tmp;

                    } else
                        ++emptyHoleCount;
                }

                return (emptyHoleCount == 6 ? playerTaking - opponentTaking : min);
            }
        }

        int HardAI::max(Gameboard state, unsigned int depth, unsigned int playerTaking, unsigned int opponentTaking, TAlphaBeta alphaBeta) const {
            if (depth == 0)
                return evaluate(state, playerTaking, opponentTaking, _number);
            else {
                int max = -100;
                int emptyHoleCount = 0;
                int tmp;

                for (unsigned int i = _firstHoleNumber; i <= _lastHoleNumber; ++i) {
                    if (state.getHoleSeedCount(i) > 0) {
                        Gameboard finalState = state;
                        int taking = state.simulate(i, finalState);

                        tmp = min(finalState, depth - 1, playerTaking + taking, opponentTaking, alphaBeta);

                        if (tmp >= alphaBeta.beta)		// Coupure β
                            return tmp;

                        if (tmp > max)
                            max = tmp;

                        if (tmp > alphaBeta.alpha)
                            alphaBeta.alpha = tmp;
                    } else
                        ++emptyHoleCount;
                }

                return (emptyHoleCount == 6 ? playerTaking - opponentTaking : max);
            }
        }
    }
}

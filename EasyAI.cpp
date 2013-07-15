#include "EasyAI.hpp"

#include <QtConcurrent/QtConcurrent>

#include "AI.hpp"

namespace QAwale {
    namespace Core {
        static unsigned int DEPTH = 6;

        EasyAI::EasyAI(unsigned int number, const QString &name) : APlayer(number, name) {
            _firstHoleNumber = _number == 1 ? 0 : 6;
            _lastHoleNumber = _number == 1 ? 4 : 11;
        }

        int EasyAI::play(const Gameboard &state) {
            int max = -1000;
            int position = _lastHoleNumber;

            QMap<int, QFuture<int> > threads;
            for (unsigned int i = _firstHoleNumber; i < _lastHoleNumber; ++i) {
                if (state.getHoleSeedCount(i) > 0) {
                    Gameboard finalState;
                    unsigned int taking = state.simulate(i, finalState);
                    QFuture<int> thread = QtConcurrent::run(this, &EasyAI::min, finalState, DEPTH, taking, 0);
                    threads.insert(i, thread);
                }
            }

            QMapIterator<int, QFuture<int> > iterator(threads);
            while (iterator.hasNext()) {
                iterator.next();
                if (iterator.value().result() > max) {
                    max = iterator.value().result();
                    position = iterator.key();
                }
            }

            return position;
        }

        int EasyAI::min(Gameboard state, unsigned int depth, int playerTaking, int opponentTaking) const {
            if (depth == 0)
                return evaluate(state, playerTaking, opponentTaking, _number);
            else {
                int min = 500;
                int emptyHoleCount = 0;
                int tmp;

                for (unsigned int i = _firstHoleNumber; i < _lastHoleNumber; ++i) {
                    if (state.getHoleSeedCount(i) > 0) {
                        Gameboard finalState = state;
                        int taking = state.simulate(i, finalState);

                        tmp = max(finalState, depth - 1, playerTaking, opponentTaking + taking);

                        if (tmp < min)
                            min = tmp;
                    } else
                        ++emptyHoleCount;
                }

                return (emptyHoleCount == 6 ? playerTaking - opponentTaking : min);
            }
        }

        int EasyAI::max(Gameboard state, int depth, int playerTaking, int opponentTaking) const {
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

                        tmp = min(finalState, depth - 1, playerTaking + taking, opponentTaking);

                        if (tmp > max)
                            max = tmp;
                    } else
                        ++emptyHoleCount;
                }

                return (emptyHoleCount == 6 ? playerTaking - opponentTaking : max);
            }
        }
    }
}


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
                    // TODO : compile error on QtConcurrent::run with msvc 2010
                    /*
                    c:\qt\qt5.0.1\5.0.1\msvc2010\include\qtconcurrent\qtconcurrentrun.h:146: erreur : C2064: le terme ne correspond pas … une fonction qui prend 5 arguments
                    EasyAI.cpp(24)ÿ: voir la r‚f‚rence … l'instanciation de la fonction modŠle 'QFuture<T> QtConcurrent::run<QAwale::Core::EasyAI*,int(__thiscall QAwale::Core::EasyAI::* )(const QAwale::Core::Gameboard &,unsigned int,int,int) const,QAwale::Core::Gameboard,unsigned int,unsigned int,int>(Functor,const Arg1 &,const Arg2 &,const Arg3 &,const Arg4 &,const Arg5 &)' en cours de compilation
                    with
                    [
                        T=int,
                        Functor=QAwale::Core::EasyAI *,
                        Arg1=int (__thiscall QAwale::Core::EasyAI::* )(const QAwale::Core::Gameboard &,unsigned int,int,int) const,
                        Arg2=QAwale::Core::Gameboard,
                        Arg3=unsigned int,
                        Arg4=unsigned int,
                        Arg5=int
                    ]
                    */
                    //QFuture<int> thread = QtConcurrent::run(this, &EasyAI::min, finalState, DEPTH, taking, 0);
                    //threads.insert(i, thread);
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

        int EasyAI::min(const Gameboard &state, unsigned int depth, int playerTaking, int opponentTaking) const {
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

        int EasyAI::max(const Gameboard& state, int depth, int playerTaking, int opponentTaking) const {
            if (depth == 0)
                return evaluate(state, playerTaking, opponentTaking, _number);
            else {
                int max = -100;
                int emptyHoleCount = 0;
                int tmp;
                int startHoleNumber = _number == 1 ? 0 : 6;
                int endHoleNumber = _number == 1 ? 5 : 11;

                for (int i = startHoleNumber; i <= endHoleNumber; ++i) {
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


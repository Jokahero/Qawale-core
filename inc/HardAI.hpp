#ifndef __HARDAI_HPP__
#define __HARDAI_HPP__

#include "AI.hpp"

namespace QAwale {
    namespace Core {
        typedef struct {
            int alpha;
            int beta;
        } TAlphaBeta;

        class HardAI : public AI {
            Q_OBJECT

        public:
            HardAI(int number, const QString& name);

            virtual int play(const Gameboard& state);

        private:
            static const unsigned int DEPTH = 10;

            int min(Gameboard state, unsigned int depth, unsigned int playerTaking, unsigned int opponentTaking, TAlphaBeta alphaBeta) const;
            int max(Gameboard state, unsigned int depth, unsigned int playerTaking, unsigned int opponentTaking, TAlphaBeta alphaBeta) const;
        };
    }
}

#endif // __HARDAI_HPP__

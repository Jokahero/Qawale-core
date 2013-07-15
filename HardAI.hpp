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
            static const unsigned int HARD_AI_DEPTH = 10;

            virtual int min(const Gameboard& state, unsigned int depth, unsigned int playerTaking, unsigned int opponentTaking);
            virtual int max(const Gameboard& state, unsigned int depth, unsigned int playerTaking, unsigned int opponentTaking);
        };
    }
}

#endif // __HARDAI_HPP__

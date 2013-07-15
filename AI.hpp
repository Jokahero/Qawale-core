#ifndef __AI_HPP__
#define __AI_HPP__

#include "APlayer.hpp"
#include "Gameboard.hpp"

namespace QAwale {
    namespace Core {
        namespace Types {
            enum PlayerType {
                Person,
                EasyAI,
                HardAI
            };
        }

        int evaluate(const Gameboard& state, int playerTaking, int opponentTaking, int number);

        class AI : public APlayer {
        public :
            AI(unsigned int number, const QString& name);

            virtual int play(const Gameboard &state) = 0;

        protected:
            static const unsigned int DEPTH;

            unsigned int _firstHoleNumber;
            unsigned int _lastHoleNumber;

            virtual int min(Gameboard state, unsigned int depth, unsigned int playerTaking, unsigned int opponentTaking) const = 0;
            virtual int max(Gameboard state, unsigned int depth, unsigned int playerTaking, unsigned int opponentTaking) const = 0;
        };
    }
}

#endif // __AI_HPP__

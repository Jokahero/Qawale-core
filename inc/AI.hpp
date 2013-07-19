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
            unsigned int _firstHoleNumber;
            unsigned int _lastHoleNumber;
        };
    }
}

#endif // __AI_HPP__

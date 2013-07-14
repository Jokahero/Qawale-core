#ifndef __AI_HPP__
#define __AI_HPP__

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
    }
}

#endif // __AI_HPP__

#include "IA.hpp"

namespace QAwale {
    namespace Core {
        int evaluate(const Gameboard &state, int playerTaking, int opponentTaking, int playerNumber) {
            int startHoleNumber = playerNumber == 2 ? 0 : 6;
            int endHoleNumber = playerNumber == 2 ? 5 : 11;
            int seedCount = 0;

            for (int i = startHoleNumber; i <= endHoleNumber; ++i)
                seedCount += state.getHoleSeedCount(i);

            if (seedCount > 0)
                return playerTaking - opponentTaking;
            else
                return -1000;
        }
    }
}

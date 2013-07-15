#include "AI.hpp"

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

        static unsigned int DEPTH = 6;

        AI::AI(unsigned int number, const QString &name) : APlayer(number, name) {
            _firstHoleNumber = _number == 1 ? 0 : 6;
            _lastHoleNumber = _number == 1 ? 4 : 11;
        }
    }
}

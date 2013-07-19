#include "Player.hpp"

namespace QAwale {
    namespace Core {
        Player::Player(int number, const QString &name) : APlayer(number, name) {}

        int Player::play(const Gameboard &state) {
            Q_UNUSED(state);

            emit holeSelectionRequested();

            waitForSignal(this, SIGNAL(holeSelected()));

            return _playedHoleNumber;
        }

        void Player::onHoleSelected(int holeNumber) {
            _playedHoleNumber = holeNumber;
            emit holeSelected();
        }
    }
}

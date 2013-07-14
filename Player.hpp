#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "APlayer.hpp"

namespace QAwale {
    namespace Core {
        class Player : public APlayer {
            Q_OBJECT

        public:
            Player(int number, const QString& name);

            virtual int play(const Gameboard& state);

        public slots:
            void onHoleSelected(int holeNumber);

        signals:
            void holeSelected();
            void holeSelectionRequested();

        private:
            unsigned int _playedHoleNumber;
        };
    }
}
#endif // PLAYER_HPP

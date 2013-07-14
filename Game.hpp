#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <QObject>

#include "AI.hpp"

namespace QAwale {
    namespace Core {
        class Player;
    }
}

namespace QAwale {
    namespace Core {
        class Game : public QObject {
            Q_OBJECT

        public:
            Game();
            virtual ~Game();

        signals:
            void init(Player* firstPlayer, Player* secondPlayer);
            void roundSwap(Player* player);
            void seedCountChanged(unsigned int holeNumber, unsigned int amount);
            void playerPlayed(unsigned int holeNumber, unsigned int playerNumber);
            void gameEnded(Player* winner);
            void quit();

        public slots:
            void onInit(const QString& firstPlayerName, PlayerType firstPlayerType, const QString& secondPlayer, PlayerType secondPlayerType);

        private:
            Player*     _firstPlayer;
            Player*     _secondPlayer;
            Gameboard   _gameboard;

            Player* createPlayer(const QString& name, PlayerType type, int number);
            void start();
        };
    }
}
#endif // __GAME_HPP__

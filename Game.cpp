#include "Game.hpp"

#include "Gameboard.hpp"
#include "AI.hpp"
#include "Player.hpp"

namespace QAwale {
    namespace Core {
        Game::Game() {
            _firstPlayer = NULL;
            _secondPlayer = NULL;
        }

        Game::~Game() {
            delete _firstPlayer;
            delete _secondPlayer;
        }

        void Game::onInit(const QString& firstPlayerName, PlayerType firstPlayerType, const QString& secondPlayerName, PlayerType secondPlayerType) {
            delete _firstPlayer;
            _firstPlayer = NULL;
            delete _secondPlayer;
            _secondPlayer = NULL;

            _firstPlayer = createPlayer(firstPlayerName, firstPlayerType, 1);
            _secondPlayer = createPlayer(secondPlayerName, secondPlayerType, 2);

            emit init(_firstPlayer, _secondPlayer);

            start();
        }

        Player* Game::createPlayer(const QString &name, PlayerType type, int number) {
            Player* player = NULL;
            switch (type) {
                case Person :
                    // TODO: create IPlayer class
                    break;
                case EasyAI :
                    // TODO : create EasyIAPlayer  class
                    break;
                case HardAI :
                    // TODO : create HardIAPlayer class
                    break;
            }

            if (player)
                connect(this, SIGNAL(quit()), player, SLOT(quit()));

            return player;
        }

        void Game::start() {
            int playerNumberToPlay = 1;
            while (!_gameboard.isGameEnded()) {
                Player* player = playerNumberToPlay == 1 ? _firstPlayer : _secondPlayer;
                emit roundSwap(player);

                Gameboard savedState = _gameboard;
                unsigned int position = player->play_t(_gameboard);
                emit playerPlayed(position, playerNumberToPlay);

                player->catchSeeds(_gameboard.play(position));

                for (int i = 0; i < 12; ++i) {
                    if (savedState.getHoleSeedCount(i) != _gameboard.getHoleSeedCount(i))
                        emit seedCountChanged(position, _gameboard.getHoleSeedCount(i));
                }

                playerNumberToPlay = 3 - playerNumberToPlay;
            }

            Player* winner = _firstPlayer->seedCount() > _secondPlayer->seedCount() ? _firstPlayer : _secondPlayer;
            emit gameEnded(winner);
        }
    }
}


#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <QObject>
#include <QFuture>
#include <QFutureWatcher>

#include "Gameboard.hpp"

namespace QAwale {
    namespace Core {
        class APlayer : public QObject {
            Q_OBJECT

        public:
            APlayer(int number, const QString& name, QObject* parent = 0);

            virtual int play(const Gameboard& state) = 0;
            int play_t(const Gameboard& state);

            inline int seedCount() const;
            inline QString name() const;
            inline int number() const;

            void catchSeeds(int amount);

        public slots:
            void quit();

        signals:
            void seedsCaught(int amount);

        private:
            QString             _name;
            int                 _seedCount;
            int                 _number;
            QFuture<int>        _future;
            QFutureWatcher<int> _futureWatcher;
        };

        inline int APlayer::seedCount() const {
            return _seedCount;
        }

        inline QString APlayer::name() const {
            return _name;
        }

        inline int APlayer::number() const {
            return _number;
        }

        void waitForSignal(QObject* object, const char* signal);
    }
}
#endif // __PLAYER_HPP__

#include "APlayer.hpp"

#include <QEventLoop>
#include <QtConcurrent/QtConcurrent>

namespace QAwale {
    namespace Core {
        APlayer::APlayer(int number, const QString& name, QObject* parent) : QObject(parent), _name(name), _seedCount(0), _number(number) {}

        void waitForSignal(QObject* object, const char* signal) {
            QEventLoop loop;
            QObject::connect(object, signal, &loop, SLOT(quit()));
            loop.exec();
        }

        int APlayer::play_t(const Gameboard& state) {
            _future = QtConcurrent::run(this, &APlayer::play, state);
            _futureWatcher.setFuture(_future);
            waitForSignal(&_futureWatcher, SIGNAL(finished()));
            return _future.result();
        }

        void APlayer::catchSeeds(int amount) {
            _seedCount += amount;
            emit seedsCaught(amount);
        }

        void APlayer::quit() {
            _futureWatcher.cancel();
            _future.cancel();
        }
    }
}

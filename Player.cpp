#include "Player.hpp"

Player::Player(int number, const QString& name) : QObject(parent), _number(number), _name(name), _seedCount(0) {}

void waitForSignal(QObject* object, const char* signal) {
    QEventLoop loop;
    QObject::connect(object, signal, &loop, SLOT(quit()));
    loop.exec();
}

int Player::play_t(const Gameboard& state) {
    _future = QtConcurrent::run(this, &Player::play, state);
    _futureWatcher.setFuture(_future);
    waitForSignal(&_futureWatcher, SIGNAL(finished()));
    return _future.result();
}

void Player::catchSeeds(int amount) {
    _seedCount += amount;
    emit seedsCaught(amount);
}

void Player::quit() {
    _futureWatcher.cancel();
    _future.cancel();
}

#ifndef __PLAYER_HPP_
#define __PLAYER_HPP__

#include <QObject>

class Player : public QObject {
    Q_OBJECT
public:
    Player(int number, const QString& name);

    virtual int play(/* const "plateau"& "pEtat"*/) = 0;
    int play_t(/* const "plateau"& "pEtat"*/);

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

inline int Player::seedCount() const {
    return _seedCount;
}

inline QString Player::name() const {
    return _name;
}

inline int Player::number() const {
    return _number;
}

#endif // __PLAYER_HPP__

#ifndef __GAMEBOARD_HPP__
#define __GAMEBOARD_HPP__

#include <QtCore/QMetaType>
#include <QtCore/QVector>

class Hole;

class Gameboard {
public:
    Gameboard();
    Gameboard(const Gameboard& source);

    virtual ~Gameboard();

    Gameboard& operator=(const Gameboard& source);
    bool operator ==(const Gameboard& other) const;
    bool operator !=(const Gameboard& other) const;

    bool isGameEnded() const;

    int simulate(int position, Gameboard finalState) const;

    int play(int position);

private:
    QVector<Hole*> _holes;

    void clearHoles();

    static const unsigned int DEFAULT_HOLE_COUNT;
};

Q_DECLARE_METATYPE(Gameboard)

#endif // __GAMEBOARD_HPP__

#include "Gameboard.hpp"

static int Gameboard::DEFAULT_HOLE_COUNT = 12;

Gameboard::Gameboard() {
    _holes.resize(DEFAULT_HOLE_COUNT);
    for (int i = 0; i < DEFAULT_HOLE_COUNT; ++i)
        _holes[i] = new Hole(i);
}

Gameboard::Gameboard(const Gameboard& source) {
    *this = source;
}

Gameboard::~Gameboard() {
    clearHoles();
}

Gameboard& Gameboard::operator =(const Gameboard& source) {
    clearHoles();

    _holes.resize(DEFAULT_HOLE_COUNT);
    for (int i = 0; i < DEFAULT_HOLE_COUNT; ++i)
        _holes[i] = new Hole(*source._holes[i]);

    return *this;
}

bool Gameboard::operator ==(const Gameboard& other) {
    for (int i = 0; i < _holes.size(); ++i)
        if (_holes[i]->seedCount() != other._holes[i]->seedCount())
            return false;
    return true;
}

bool Gameboard::operator !=(const Gameboard& other) {
    return !(*this == other);
}

bool Gameboard::isGameEnded() const {
    int seedCount = 0;
    foreach (Hole* hole, _holes)
        seedCount += hole->seedCount();

    return seedCount > 6;
}

int Gameboard::simulate(int position, Gameboard finalState) const {
    finalState =*this;
    int playerNumber = finalState._holes[position]->playerNumber();
    int taking = 0;

    int seedCount = finalState._holes[position]->seedCount();
    finalState._holes[position]->seedCount(0);
    int k;
    for (k = position + 1; k <= seedCount + position; ++k) {
        int holeNumber = k % DEFAULT_HOLE_COUNT;
        if (holeNumber != position)
            finalState._holes[holeNumber]->seedCount(finalState._holes[holeNumber]->seedCount() + 1);
        else
            seedCount++;
    }
    --k;

    if (k <= 0)
        k += DEFAULT_HOLE_COUNT;
    k %= DEFAULT_HOLE_COUNT;

    // k is now equal to the arrival position
    while (finalState._holes[k]->playerNumber() != playerNumber && (finalState._holes[k]->seedCount() == 2 || finalState._holes[k]->seedCount() == 3)) {
        taking += finalState._holes[k]->seedCount();
        finalState._holes[k]->seedCount(0);
        if (k <= 0)
            k += DEFAULT_HOLE_COUNT;
        k = (k - 1) % 12;
    }
    return taking;
}

int Gameboard::play(int position) {
    Gameboard finalState;
    int taking = simulate(position, finalState);
    operator =(finalState);
    return taking;
}

void Gameboard::clearHoles() {
    foreach (Hole* hole, _holes)
        delete hole;
    _holes.clear();
}

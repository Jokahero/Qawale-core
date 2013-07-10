#ifndef __IA_HPP__
#define __IA_HPP__

#include "Gameboard.hpp"

enum TypesJoueurs {
    Joueur,
    IAFacile,
    IADifficile
};

int evaluate(const Gameboard& state, int playerTaking, int opponentTaking, int number);

#endif // __IA_HPP__

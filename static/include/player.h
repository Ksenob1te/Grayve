#ifndef GRAYVE_PLAYER_H
#define GRAYVE_PLAYER_H
#include "character.h"

class Player: public Character {
public:
    explicit Player(field::Map *map) : Character(map) {};
};

#endif //GRAYVE_PLAYER_H

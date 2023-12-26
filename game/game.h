#ifndef GRAYVE_GAME_H
#define GRAYVE_GAME_H
#include "map.h"
#include "camera.h"
#include "controller.h"
#include "player.h"
#include "enemy.h"

class Game {
protected:
    field::Map globalMap;
    Player *mainChar;
    Camera globalCam;

public:
    Game();
    void update();
    void render(double interpolation);
};

extern Game globalGame;
#endif //GRAYVE_GAME_H

#ifndef GRAYVE_GAME_H
#define GRAYVE_GAME_H
//#include "SFML/Graphics.hpp"
#include "entity.h"
#include "map.h"
#include "camera.h"
#include "controller.h"

class Game {
protected:
    int tick_rate;
    field::Map globalMap;
    Entity mainChar;
    Camera globalCam;

public:
    Game();
    void update();
    void render(double interpolation);
};

extern Game globalGame;
#endif //GRAYVE_GAME_H

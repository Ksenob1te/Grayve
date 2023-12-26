#ifndef GRAYVE_GAME_H
#define GRAYVE_GAME_H
#include "map.h"
#include "camera.h"
#include "controller.h"
#include "player.h"
#include "enemy.h"

#define TICK_RATE 50
#define TICK_TIMER (1000./TICK_RATE)
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Game {
protected:
    field::Map globalMap;
    Player *mainChar;
    Camera globalCam;
    double interpolation{};

public:
    Game();
    static void setupEngine();
    static void tickrateManager();
    static void calcFPS();
    static void renderStatic();
    static void enableMultisample(int);

    void update();
    void render();

};

extern Game globalGame;
#endif //GRAYVE_GAME_H

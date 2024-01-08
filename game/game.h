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

/**
 * @brief The Game class manages the game state and rendering.
 */
class Game {
protected:
    field::Map globalMap;  ///< The game's global map.
    Player* mainChar;      ///< The main player character.
    Camera globalCam;       ///< The game's global camera.
    double interpolation;  ///< Interpolation value for smooth rendering.

public:
    /**
     * @brief Constructor for the Game class.
     */
    Game();

    /**
     * @brief Sets up the game engine.
     */
    static void setupEngine();

    /**
     * @brief Manages the tick rate of the game.
     */
    static void tickrateManager();

    /**
     * @brief Calculates frames per second (FPS).
     */
    static void calcFPS();

    /**
      * @brief Renders static elements of the game.
      */
    static void renderStatic();

    /**
     * @brief Enables multisampling.
     * @param sampleCount The number of samples to use for multisampling.
     */
    static void enableMultisample(int);

    /**
     * @brief Updates the game logic.
     */
    void update();

    /**
     * @brief Renders the game world.
     */
    void render();

};


/**
 * @brief The global instance of the Game class.
 */
extern Game globalGame;
#endif //GRAYVE_GAME_H

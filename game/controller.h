#ifndef GRAYVE_CONTROLLER_H
#define GRAYVE_CONTROLLER_H
#include "player.h"
#include "camera.h"

namespace controller {
    /**
     * @brief Function to handle mouse motion events.
     * @param x The x-coordinate of the mouse.
     * @param y The y-coordinate of the mouse.
     */
    void mouseMotion(int x, int y);

    /**
     * @brief Function to handle special key actions.
     * @param key The special key code.
     * @param The x-coordinate of the mouse.
     * @param The y-coordinate of the mouse.
     */
    void specialKeyAction(int key, int, int);

    /**
     * @brief Function to reset special key actions.
     * @param key The special key code.
     * @param The x-coordinate of the mouse.
     * @param The y-coordinate of the mouse.
     */
    void specialKeyReset(int key, int, int);

    /**
     * @brief Function to handle normal key actions.
     * @param key The key pressed.
     * @param The x-coordinate of the mouse.
     * @param The y-coordinate of the mouse.
     */
    void normalKeyAction(unsigned char key, int, int);

    /**
     * @brief Function to reset normal key actions.
     * @param key The key pressed.
     * @param The x-coordinate of the mouse.
     * @param The y-coordinate of the mouse.
     */
    void normalKeyReset(unsigned char key, int, int);

    /**
     * @brief Function to handle mouse events.
     * @param button The mouse button involved.
     * @param state The state of the mouse button.
     * @param x The x-coordinate of the mouse.
     * @param y The y-coordinate of the mouse.
     */
    void mouseEvent(int button, int state, int x, int y);

    /**
     * @brief Function for idle operations.
     */
    void idleFunc();

    /**
     * @brief Controller class for managing player and camera actions.
     */
    class Controller {
    protected:
        bool pressed_forward, pressed_left, pressed_right, pressed_backward;
        int mouseDeltaX, mouseDeltaZ;
        bool pressed_lb{}, pressed_rb{}, pressed_shift{};
    public:
        /**
         * @brief Default constructor for the Controller class.
         */
        Controller() : pressed_right(false), pressed_forward(false), pressed_left(false), pressed_backward(false),
                       mouseDeltaX(0), mouseDeltaZ(0) {};

        /**
         * @brief Process the actions for the provided player.
         * @param player The player object to process actions for.
         */
        void process_player(Player &player);

        /**
         * @brief Process the actions for the provided camera.
         * @param camera The camera object to process actions for.
         */
        void process_camera(Camera &camera);

        friend void mouseMotion(int x, int y);
        friend void specialKeyAction(int key, int, int);
        friend void specialKeyReset(int key, int, int);
        friend void normalKeyAction(unsigned char key, int, int);
        friend void normalKeyReset(unsigned char key, int, int);
        friend void mouseEvent(int button, int state, int x, int y);
        friend void idleFunc();

    };

    /**
     * @brief Extern instance of the Controller used globally.
     */
    extern Controller globalController;
}

#endif //GRAYVE_CONTROLLER_H

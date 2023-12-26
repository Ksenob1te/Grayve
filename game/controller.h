#ifndef GRAYVE_CONTROLLER_H
#define GRAYVE_CONTROLLER_H
#include "player.h"
#include "camera.h"

namespace controller {
    void mouseMotion(int x, int y);
    void specialKeyAction(int key, int, int);
    void specialKeyReset(int key, int, int);
    void normalKeyAction(unsigned char key, int, int);
    void normalKeyReset(unsigned char key, int, int);
    void mouseEvent(int button, int state, int x, int y);
    void idleFunc();

    class Controller {
    protected:
        bool pressed_forward, pressed_left, pressed_right, pressed_backward;
        int mouseDeltaX, mouseDeltaZ;
        bool pressed_lb{}, pressed_rb{}, pressed_shift{};
    public:
        Controller() : pressed_right(false), pressed_forward(false), pressed_left(false), pressed_backward(false),
                       mouseDeltaX(0), mouseDeltaZ(0) {};
        void process_player(Player &player);
        void process_camera(Camera &camera);

        friend void mouseMotion(int x, int y);
        friend void specialKeyAction(int key, int, int);
        friend void specialKeyReset(int key, int, int);
        friend void normalKeyAction(unsigned char key, int, int);
        friend void normalKeyReset(unsigned char key, int, int);
        friend void mouseEvent(int button, int state, int x, int y);
        friend void idleFunc();

    };

    extern Controller globalController;
}

#endif //GRAYVE_CONTROLLER_H

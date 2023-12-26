#include "controller.h"

namespace controller {
    Controller globalController = Controller();

    void mouseMotion(int x, int y) {
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
            globalController.pressed_shift = true;
        
        globalController.mouseDeltaX = x - 640;
        globalController.mouseDeltaZ = y - 360;
    }

    void idleFunc() {}

    void mouseEvent(int button, int state, int, int) {
        if (button == GLUT_LEFT_BUTTON)
            globalController.pressed_lb = (state == GLUT_DOWN);

        else if (button == GLUT_RIGHT_BUTTON)
            globalController.pressed_rb = (state == GLUT_DOWN);
    }

    void specialKeyAction(int key, int, int) {
        switch (key) {
            case GLUT_KEY_LEFT:
                globalController.pressed_left = true;
                break;
            case GLUT_KEY_RIGHT:
                globalController.pressed_right = true;
                break;
            case GLUT_KEY_UP:
                globalController.pressed_forward = true;
                break;
            case GLUT_KEY_DOWN:
                globalController.pressed_backward = true;
                break;
            default:
                break;
        }
    }

    void normalKeyAction(unsigned char key, int, int) {
        switch (tolower(key)) {
            case 'w':
                globalController.pressed_forward = true;
                break;
            case 'a':
                globalController.pressed_left = true;
                break;
            case 's':
                globalController.pressed_backward = true;
                break;
            case 'd':
                globalController.pressed_right = true;
                break;
            default:
                break;
        }
    }

    void specialKeyReset(int key, int, int) {
        switch (key) {
            case GLUT_KEY_LEFT:
                globalController.pressed_left = false;
                break;
            case GLUT_KEY_RIGHT:
                globalController.pressed_right = false;
                break;
            case GLUT_KEY_UP:
                globalController.pressed_forward = false;
                break;
            case GLUT_KEY_DOWN:
                globalController.pressed_backward = false;
                break;
            default:
                break;
        }
    }

    void normalKeyReset(unsigned char key, int, int) {
        switch (tolower(key)) {
            case 'w':
                globalController.pressed_forward = false;
                break;
            case 'a':
                globalController.pressed_left = false;
                break;
            case 's':
                globalController.pressed_backward = false;
                break;
            case 'd':
                globalController.pressed_right = false;
                break;
            default:
                break;
        }
    }

    void Controller::process_player(Player &player) {
        player.setMoveForward(this->pressed_forward);
        player.setMoveLeft(this->pressed_left);
        player.setMoveBackward(this->pressed_backward);
        player.setMoveRight(this->pressed_right);
        player.set_shoot_action(this->pressed_lb);
        if (this->pressed_shift) {
            player.set_sprint(this->pressed_shift);
            this->pressed_shift = false;
        }
    }

    void Controller::process_camera(Camera &camera) {
        camera.setPhi(camera.getPhi() + (double) this->mouseDeltaX * 0.001f);
        camera.changeTheta((double) this->mouseDeltaZ * 0.0005f);

        camera.follow->setPhi(camera.getPhi());
        glutPostRedisplay();
        if (this->mouseDeltaX || this->mouseDeltaZ)
            glutWarpPointer(640, 360);
        this->mouseDeltaZ = 0;
        this->mouseDeltaX = 0;
    }
}
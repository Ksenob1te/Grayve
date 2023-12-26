#include <GL/glut.h>
#include "game/game.h"

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    Game::setupEngine();
    glutMainLoop();
}

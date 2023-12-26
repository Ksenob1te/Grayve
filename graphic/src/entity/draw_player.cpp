#include "draw_player.h"
#include "GL/gl.h"
#include "GL/glut.h"

void draw::draw_player(const Entity &player, double interpolation) {
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslated(
            player.get_interpolatedX(interpolation),
            player.getY() + 0.3,
            player.get_interpolatedZ(interpolation)
    );
    glutSolidSphere(0.3, 30, 30);
    glPopMatrix();
}

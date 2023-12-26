#include "draw_enemy.h"
#include "GL/gl.h"
#include "GL/glut.h"

void draw::draw_enemy(const Entity &enemy, double interpolation) {
    glColor3f(0.3, 0.3, 0.3);
    glPushMatrix();
    glTranslated(
            enemy.get_interpolatedX(interpolation),
            enemy.getY() + 0.3,
            enemy.get_interpolatedZ(interpolation)
    );
    glutSolidSphere(0.3, 30, 30);
    glPopMatrix();
}

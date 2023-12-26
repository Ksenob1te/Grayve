#include "draw_projectile.h"
#include "GL/gl.h"
#include "GL/glut.h"

void draw::draw_projectile(const Entity &projectile, double interpolation) {
    glColor3f(0.640, 0.156, 0.129);
    glPushMatrix();
    glTranslated(
            projectile.get_interpolatedX(interpolation),
            projectile.getY() + 0.5,
            projectile.get_interpolatedZ(interpolation)
    );
    glutSolidSphere(0.15, 30, 30);
    glPopMatrix();
}
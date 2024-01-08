#include "draw_player.h"
#include "GL/gl.h"
#include "GL/glut.h"

void draw::draw_player(const Entity &player, double interpolation) {
    double right_x = player.get_interpolatedX(interpolation) - cos(player.getPhi() - M_PI_2) * 0.3;
    double right_z = player.get_interpolatedZ(interpolation) - sin(player.getPhi() - M_PI_2) * 0.3;

    double left_x = player.get_interpolatedX(interpolation) - cos(player.getPhi() + M_PI_2) * 0.3;
    double left_z = player.get_interpolatedZ(interpolation) - sin(player.getPhi() + M_PI_2) * 0.3;

    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glVertex3d(left_x, 0, left_z);
    glVertex3d(left_x, 1, left_z);
    glVertex3d(right_x, 1, right_z);
    glVertex3d(right_x, 0, right_z);
    glEnd();

//    glColor3f(1, 1, 1);
//    glPushMatrix();
//    glTranslated(
//            player.get_interpolatedX(interpolation),
//            player.getY() + 0.3,
//            player.get_interpolatedZ(interpolation)
//    );
//    glutSolidSphere(0.3, 30, 30);
//    glPopMatrix();
}

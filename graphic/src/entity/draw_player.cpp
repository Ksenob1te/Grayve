#include "draw_player.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "texture_manager.h"

void draw::draw_player(const Entity &player, double interpolation) {
    double right_x = player.get_interpolatedX(interpolation) - cos(player.getPhi() - M_PI_2) * 0.35;
    double right_z = player.get_interpolatedZ(interpolation) - sin(player.getPhi() - M_PI_2) * 0.35;

    double left_x = player.get_interpolatedX(interpolation) - cos(player.getPhi() + M_PI_2) * 0.35;
    double left_z = player.get_interpolatedZ(interpolation) - sin(player.getPhi() + M_PI_2) * 0.35;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);

    float animation = 1;
    if (player.isMovingForward())
        animation = 1;
    if (player.isMovingBackward())
        animation = 5;
    if (player.isMovingLeft())
        animation = 7;
    if (player.isMovingRight())
        animation = 3;
    if (player.isMovingForward() && player.isMovingLeft())
        animation = 0;
    if (player.isMovingForward() && player.isMovingRight())
        animation = 2;
    if (player.isMovingBackward() && player.isMovingLeft())
        animation = 6;
    if (player.isMovingBackward() && player.isMovingRight())
        animation = 4;

    glBindTexture(GL_TEXTURE_2D, texture_manager->getTexture("player"));
    glBegin(GL_QUADS);

    glTexCoord2f((1.0f/8.0f) * (animation), 0.99f);	glVertex3d(left_x, 0, left_z);
    glTexCoord2f((1.0f/8.0f) * (animation), 0.0f);	glVertex3d(left_x, 1.25, left_z);
    glTexCoord2f((1.0f/8.0f) * (animation + 1), 0.0f);	glVertex3d(right_x, 1.25, right_z);
    glTexCoord2f((1.0f/8.0f) * (animation + 1), 0.99f);	glVertex3d(right_x, 0, right_z);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

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

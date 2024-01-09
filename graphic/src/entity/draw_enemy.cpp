#include "draw_enemy.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "array"
#include "texture_manager.h"

void draw::draw_enemy(const Entity &enemy, double interpolation) {

    double right_x = enemy.get_interpolatedX(interpolation) - cos(enemy.getPhi() - M_PI_2) * 0.35;
    double right_z = enemy.get_interpolatedZ(interpolation) - sin(enemy.getPhi() - M_PI_2) * 0.35;

    double left_x = enemy.get_interpolatedX(interpolation) - cos(enemy.getPhi() + M_PI_2) * 0.35;
    double left_z = enemy.get_interpolatedZ(interpolation) - sin(enemy.getPhi() + M_PI_2) * 0.35;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture_manager->getTexture("enemy"));
    glBegin(GL_QUADS);
    glTexCoord2f((1.0f/8.0f) * (5), 0.99f);	glVertex3d(left_x, 0, left_z);
    glTexCoord2f((1.0f/8.0f) * (5), 0.0f);	glVertex3d(left_x, 1.25, left_z);
    glTexCoord2f((1.0f/8.0f) * (5 + 1), 0.0f);	glVertex3d(right_x, 1.25, right_z);
    glTexCoord2f((1.0f/8.0f) * (5 + 1), 0.99f);	glVertex3d(right_x, 0, right_z);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

//    glColor3f(0.3, 0.3, 0.3);
//    glPushMatrix();
//    double cordX = enemy.get_interpolatedX(interpolation);
//    double cordY = enemy.getY() + 0.3;
//    double cordZ = enemy.get_interpolatedZ(interpolation);
//    glTranslated(cordX, cordY, cordZ);
//    glutSolidSphere(0.3, 30, 30);
//    glPopMatrix();
}

#include "draw_enemy.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "array"

void draw::draw_enemy(const Entity &enemy, double interpolation) {
    glColor3f(0.3, 0.3, 0.3);
    glPushMatrix();
    double cordX = enemy.get_interpolatedX(interpolation);
    double cordY = enemy.getY() + 0.3;
    double cordZ = enemy.get_interpolatedZ(interpolation);
    glTranslated(cordX, cordY, cordZ);
    glutSolidSphere(0.3, 30, 30);
    glPopMatrix();

//    std::array<GLdouble, 16> projection{};
//    std::array<GLdouble, 16> modelview{};
//    std::array<GLint, 4> viewport{};
//    std::array<GLdouble, 3>  screen_coords{};
//
//    glGetDoublev(GL_PROJECTION_MATRIX, projection.data());
//    glGetDoublev(GL_MODELVIEW_MATRIX, modelview.data());
//    glGetIntegerv(GL_VIEWPORT, viewport.data());
//
//    gluProject(cordX, cordY, cordZ,
//               modelview.data(), projection.data(), viewport.data(),
//               screen_coords.data(), screen_coords.data() + 1, screen_coords.data() + 2);
//    std::cout << screen_coords[0] << " " << screen_coords[1] << " " << screen_coords[2] << std::endl;
//
//    GLdouble points[4][3] = {
//            {screen_coords[0] - 20, screen_coords[1] + 10, 0},
//            {screen_coords[0] + 20, screen_coords[1] + 10, 0},
//            {screen_coords[0] + 20, screen_coords[1] + 15, 0},
//            {screen_coords[0] - 20, screen_coords[1] + 15, 0}
//    };


//    glMatrixMode(GL_PROJECTION);
//    glPushMatrix();
//    glLoadIdentity();
//    gluOrtho2D(0, 1280, 0, 720);
//
//    glColor3b(1, 0, 0);
//    glBegin(GL_POLYGON);
//    for (auto edge: points)
//        glVertex3dv(edge);
//    glEnd();
//
//    glPopMatrix();
//    glMatrixMode(GL_MODELVIEW);
}

//#include <GL/glut.h>
//#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "cmath"
#include "iostream"
#include "graphic/include/camera.h"
#include "chunk.h"
#include "map.h"
#include "graphic/include/draw_block.h"

Camera globalCam;
field::Map globalMap;

void CalculateFrameRate()
{
    static float framesPerSecond    = 0.0f;       // This will store our fps
    static float lastTime   = 0.0f;       // This will hold the time from the last frame
    float currentTime = GetTickCount() * 0.001f;
    ++framesPerSecond;
    if( currentTime - lastTime > 1.0f )
    {
        lastTime = currentTime;
        fprintf(stderr, "\nCurrent Frames Per Second: %d\n\n", (int)framesPerSecond);
        framesPerSecond = 0;
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    globalCam.update();
    gluLookAt(globalCam.getX(), globalCam.getY(), globalCam.getZ(),
              globalCam.getX() + globalCam.getLookX(),
              globalCam.getY() + globalCam.getLookY(),
              globalCam.getZ() + globalCam.getLookZ(),
              0.0, 1.0, 0.0);

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef((GLfloat) globalCam.follow->getX(), 0, (GLfloat) globalCam.follow->getZ());
    glutSolidSphere(0.5, 30, 30);
    glPopMatrix();

    const field::Chunk &current_chunk = globalMap.get_starter();
    for (int x = current_chunk.left_bottom.getX(); x <= current_chunk.right_top.getX(); x++) {
        for (int z = current_chunk.left_bottom.getZ(); z <= current_chunk.right_top.getZ(); z++) {
            draw::draw_block(globalMap.get_starter().room[z][x]);
        }
    }

//    glBegin(GL_LINES);
//    for (GLfloat i = -100; i <= 100; i += 1) {
//        glVertex3f(i, 0, 100); glVertex3f(i, 0, -100);
//        glVertex3f(100, 0, i); glVertex3f(-100, 0, i);
//    }
//
//    glEnd();

    CalculateFrameRate();
//    glutSwapBuffers();
    glFlush();
}

void special(int key, int, int) {
    if (!globalCam.follow->isMoving()) globalCam.follow->setPhi(globalCam.getPhi());
    switch (key) {
        case GLUT_KEY_LEFT: globalCam.follow->setMoveLeft(true); break;
        case GLUT_KEY_RIGHT: globalCam.follow->setMoveRight(true); break;
        case GLUT_KEY_UP: globalCam.follow->setMoveForward(true); break;
        case GLUT_KEY_DOWN: globalCam.follow->setMoveBackward(true); break;
        default: break;
    }
    glutPostRedisplay();
}

void reset_special(int key, int, int) {
    switch (key) {
        case GLUT_KEY_LEFT: globalCam.follow->setMoveLeft(false); break;
        case GLUT_KEY_RIGHT: globalCam.follow->setMoveRight(false); break;
        case GLUT_KEY_UP: globalCam.follow->setMoveForward(false); break;
        case GLUT_KEY_DOWN: globalCam.follow->setMoveBackward(false); break;
        default: break;
    }
}

void init_lighting() {
    GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat direction[] = { 1.0, 1.0, 1.0, 0.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);

    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, direction);

    glEnable(GL_LIGHTING);                // so the renderer considers light
    glEnable(GL_LIGHT0);
}

void init() {
    auto entity = new Entity();
    entity->setSpeed(0.003);
    globalCam.follow = entity;
    glClearColor(0, 0, 0, 1.0);
    glColor3f(1.0, 1.0, 1.0);

//    init_lighting();
    glEnable(GL_DEPTH_TEST);
    glfwWindowHint(GLFW_SAMPLES, 4);
//    glEnable(GL_MULTISAMPLE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, 16.0/9.0, 1, 150);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//    gluLookAt(2, 3, 2, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv) {
    globalMap = field::Map(10);
    globalMap.generate_room_map(15);
    globalMap.print_map();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("A Simple Tetrahedron");
    glutDisplayFunc(display);
    glutSpecialFunc(special);
    glutSpecialUpFunc(reset_special);
//    timer(0);
    init();
    glutMainLoop();
}

//    auto *map = new field::Map(19, 7);
//    map->generate_dungeon();
//    map->print_map();
//    map->print_dungeon();
//    int x;
//    std::cin >> x;
//    return 0;
//}

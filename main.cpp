#include <GL/glut.h>
#include <GL/gl.h>
#include "GL/glext.h"
#include "GL/freeglut.h"
#include "iostream"
#include "game/game.h"
#define TICK_RATE 50
#define TICK_TIMER (1000./TICK_RATE)
double globalInterpolation = 0;

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

void idleUpdateTick() {
    static int previous_tick = 0;
    static int lastTime = 0;
    static int TPS = 0;
    int current_tick = glutGet(GLUT_ELAPSED_TIME);
    if (current_tick - previous_tick <= TICK_TIMER) {
        globalInterpolation = ((double) current_tick - (double) previous_tick) / TICK_TIMER;
        return;
    }

    if(current_tick - lastTime > 1000) {
        lastTime = current_tick;
        std::cout<< "Current TPS: " << TPS << std::endl;
        TPS = 0;
    }
    static bool busy = false;
    if (busy) return;
    busy = true;
    previous_tick = current_tick;
    TPS++;
    globalGame.update();
    globalInterpolation = 0;
    busy = false;
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    globalGame.render(globalInterpolation);

    CalculateFrameRate();
    glFlush();
}

void enableMultisample(int msaa)
{
    if (msaa)
    {
        glEnable(GL_MULTISAMPLE);
        glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

        // detect current settings
        GLint iMultiSample = 5;
        GLint iNumSamples = 5;
        glGetIntegerv(GL_SAMPLE_BUFFERS, &iMultiSample);
        glGetIntegerv(GL_SAMPLES, &iNumSamples);
        printf("MSAA on, GL_SAMPLE_BUFFERS = %d, GL_SAMPLES = %d\n", iMultiSample, iNumSamples);
    }
    else
    {
        glDisable(GL_MULTISAMPLE);
        printf("MSAA off\n");
    }
}

void init() {
    glClearColor(0, 0, 0, 1.0);
    glColor3f(1.0, 1.0, 1.0);

    glEnable(GL_DEPTH_TEST);

    glutSetOption(GLUT_MULTISAMPLE, 8);
    enableMultisample(1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, 16.0/9.0, 1, 150);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("A Simple Tetrahedron");

    glutMotionFunc(controller::mouseMotion);
    glutPassiveMotionFunc(controller::mouseMotion);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(640, 360);

    glutDisplayFunc(display);
    glutIdleFunc(idleUpdateTick);

    glutSpecialFunc(controller::specialKeyAction);
    glutSpecialUpFunc(controller::specialKeyReset);
    glutKeyboardFunc(controller::normalKeyAction);
    glutKeyboardUpFunc(controller::normalKeyReset);
    glutMouseFunc(controller::mouseEvent);

    init();
    glutMainLoop();
}

//    auto *globalMap = new field::Map(19, 7);
//    globalMap->generate_dungeon();
//    globalMap->print_map();
//    globalMap->print_dungeon();
//    int x;
//    std::cin >> x;
//    return 0;
//}

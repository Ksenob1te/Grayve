#include "game.h"
#include "draw_map.h"
#include "GL/freeglut.h"
#include <GL/gl.h>
#include "GL/glext.h"
#include "texture_manager.h"

Game globalGame = Game();

void Game::calcFPS() {
    static double framesPerSecond = 0.0f;
    static double lastTime = 0.0f;
    double currentTime = (double) GetTickCount() * 0.001f;
    ++framesPerSecond;
    if (currentTime - lastTime > 1.0f) {
        lastTime = currentTime;
        fprintf(stderr, "\nCurrent Frames Per Second: %d\n\n", (int) framesPerSecond);
        framesPerSecond = 0;
    }
}

void Game::renderStatic() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    globalGame.render();
    Game::calcFPS();
    glFlush();
}

Game::Game() {
    this->globalMap = field::Map(10);
    this->globalMap.generate_room_map(15);
    this->globalMap.print_map();
    this->globalMap.print_starter();

    this->mainChar = new Player(&this->globalMap, globalMap.get_starter_x(), globalMap.get_starter_y());
    this->mainChar->setCoordinates(Point(16.5, 16.5));
    this->mainChar->setHeight(0);
    this->mainChar->setSpeed(2./20);

    auto enemy = new Enemy(&this->globalMap, globalMap.get_starter_x(), globalMap.get_starter_y());
    enemy->setCoordinates(Point(10.5, 10.5));
    enemy->setSpeed(0.05);
    enemy->set_follow(this->mainChar);

    this->globalCam.follow = this->mainChar;
}

void Game::update() {
    this->globalMap.update();

}

void Game::render() {
    controller::globalController.process_player(*mainChar);
    controller::globalController.process_camera(globalCam);
    globalCam.update(interpolation);
    int chunk_x = this->mainChar->get_chunk_x();
    int chunk_y = this->mainChar->get_chunk_y();
    draw::draw_entities(globalMap, interpolation, chunk_x, chunk_y);
    draw::draw_map(globalMap, globalCam, chunk_x, chunk_y);
}

void Game::tickrateManager() {
    static int previous_tick = 0;
    static int lastTime = 0;
    static int TPS = 0;

    int current_tick = glutGet(GLUT_ELAPSED_TIME);
    if (current_tick - previous_tick <= TICK_TIMER) {
        globalGame.interpolation = ((double) current_tick - (double) previous_tick) / TICK_TIMER;
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
    globalGame.interpolation = 0;
    busy = false;
}

void Game::enableMultisample(int msaa) {
    if (msaa) {
        glEnable(GL_MULTISAMPLE);
        glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

        GLint iMultiSample = 5;
        GLint iNumSamples = 5;
        glGetIntegerv(GL_SAMPLE_BUFFERS, &iMultiSample);
        glGetIntegerv(GL_SAMPLES, &iNumSamples);
        printf("MSAA on, GL_SAMPLE_BUFFERS = %d, GL_SAMPLES = %d\n", iMultiSample, iNumSamples);
    } else {
        glDisable(GL_MULTISAMPLE);
        printf("MSAA off\n");
    }
}

void Game::setupEngine() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("GRAYVE");

    glutMotionFunc(controller::mouseMotion);
    glutPassiveMotionFunc(controller::mouseMotion);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    glutDisplayFunc(Game::renderStatic);
    glutIdleFunc(Game::tickrateManager);

    glutSpecialFunc(controller::specialKeyAction);
    glutSpecialUpFunc(controller::specialKeyReset);
    glutKeyboardFunc(controller::normalKeyAction);
    glutKeyboardUpFunc(controller::normalKeyReset);
    glutMouseFunc(controller::mouseEvent);

    glClearColor(0, 0, 0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    Game::enableMultisample(1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, 16.0/9.0, 1, 150);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    texture_manager = new TextureManager();
}

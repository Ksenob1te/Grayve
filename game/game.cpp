#include "game.h"
#include "draw_map.h"

Game globalGame = Game();


Game::Game(): tick_rate(20) {
    this->globalMap = field::Map(10);
    this->globalMap.generate_room_map(15);
    this->globalMap.print_map();
    this->globalMap.print_starter();

    this->mainChar = Entity();
    this->mainChar.setCoordinates(Point(16.5, 16.5));
    this->mainChar.setSpeed(2./20);

    this->globalCam.follow = &this->mainChar;
}

void Game::update() {
    mainChar.setPhi(globalCam.getPhi());
    mainChar.update_position();
}

void Game::render(double interpolation) {
    controller::globalController.process_player(mainChar);
    controller::globalController.process_camera(globalCam);
    globalCam.update(interpolation);
//    std::cout << interpolation << std::endl;

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(
            globalCam.follow->get_interpolatedX(interpolation),
            0,
            globalCam.follow->get_interpolatedZ(interpolation)
            );
    glutSolidSphere(0.3, 30, 30);
    glPopMatrix();
    draw::draw_map(globalMap);
}

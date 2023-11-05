#ifndef GRAYVE_GAME_H
#define GRAYVE_GAME_H
#include "SFML/Graphics.hpp"

class Game: public sf::Drawable, public sf::Transformable {
protected:
    int tick_rate;

public:
    Game();
    ~Game();
    void init();
    bool check();

public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif //GRAYVE_GAME_H

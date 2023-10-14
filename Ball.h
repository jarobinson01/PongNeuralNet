#pragma once

#include <SFML/Graphics.hpp>

#include "Paddle.h"

class Ball {
    sf::RectangleShape ballShape;
    float x_vel;
    float y_vel;

    bool checkForCollision(const sf::FloatRect&);
    void resetBall();
public:
    Ball();

    sf::Vector2f getPosition() const { return ballShape.getPosition(); }
    void update(Paddle&, Paddle&);
    void render(sf::RenderTarget&);
};
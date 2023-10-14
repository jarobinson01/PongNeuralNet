#include <iostream>
#include <ctime>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include "Global.h"
#include "Paddle.h"
#include "Ball.h"

Ball::Ball() {
    this->ballShape.setSize(sf::Vector2f(BALL_WIDTH, BALL_HEIGHT));
    this->ballShape.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - BALL_WIDTH / 2, SCREEN_HEIGHT / 2 - BALL_HEIGHT / 2));

    this->x_vel = .1;
    this->y_vel = 0;
}

bool Ball::checkForCollision(const sf::FloatRect& paddleBounds) {
    return this->ballShape.getGlobalBounds().intersects(paddleBounds);
}

void Ball::resetBall() {
    this->ballShape.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - BALL_WIDTH / 2, SCREEN_HEIGHT / 2 - BALL_HEIGHT / 2));
    this->x_vel = (rand() % 2) ? .1 : -.1;
    this->y_vel = rand() % 25 / 100.0 - .13;
}

void Ball::update(Paddle& leftPaddle, Paddle& rightPaddle) {
    this->ballShape.move(x_vel, y_vel);

    // Paddle Collision
    if(checkForCollision(leftPaddle.getBounds()) || checkForCollision(rightPaddle.getBounds())) {
        this->x_vel *= -1.1;

        srand(time(NULL));
        y_vel = rand() % 25 / 100.0 - .13;
    }

    // Screen (Top/Bottom) Collision
    if(this->ballShape.getPosition().y <= 0 || this->ballShape.getPosition().y + BALL_HEIGHT >= SCREEN_HEIGHT) {
        this->y_vel *= -1;
    }

    // Screen (Side) Collision
    if(this->ballShape.getPosition().x <= PADDLE_WIDTH - 3|| this->ballShape.getPosition().x >= SCREEN_WIDTH - PADDLE_WIDTH - BALL_WIDTH + 3) {
        resetBall();
    }
}

void Ball::render(sf::RenderTarget& target) {
    target.draw(ballShape);
}
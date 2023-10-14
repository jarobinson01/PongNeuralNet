#include <iostream>

#include "Global.h"
#include "Paddle.h"
#include "PaddleEvent.h"

Paddle::Paddle(int side) {
    this->paddleShape.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    this->paddleShape.setFillColor(sf::Color::White);

    this->side = side;

    if(side == 0) {
        this->paddleShape.setPosition(0, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2);
    } else if(side == 1) {
        this->paddleShape.setPosition(SCREEN_WIDTH - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2);
    }
}

sf::FloatRect Paddle::getBounds() const {
    return this->paddleShape.getGlobalBounds();
}

void Paddle::update(sf::Event& event, PaddleEvent& paddleEvent) {
    float velocity[2];
    if(event.type == sf::Event::KeyPressed || event.type == sf::Event::TextEntered) {
        // LEFT PADDLE MOVEMENT
        if((char)event.text.unicode == 'w' && this->side == 0) {
            this->moveDown = false;
            this->moveUp = true;
        } else if((char)event.text.unicode == 's' && this->side == 0) {
            this->moveUp = false;
            this->moveDown = true;
        }

        // RIGHT PADDLE MOVEMENT
        if(event.key.scancode == sf::Keyboard::Scan::Up && this->side == 1) {
            this->moveDown = false;
            this->moveUp = true;
        } else if(event.key.scancode == sf::Keyboard::Scan::Down && this->side == 1) {
            this->moveUp = false;
            this->moveDown = true;
        }
    }

    if(event.type == sf::Event::KeyReleased) {
        if(event.key.scancode == sf::Keyboard::Scan::W && this->side == 0 && !moveDown) {
            this->moveUp = false;
            this->moveDown = false;
            this->x_vel = 0;
            this->y_vel = 0;
        }

        if(event.key.scancode == sf::Keyboard::Scan::S && this->side == 0 && !moveUp) {
            this->moveUp = false;
            this->moveDown = false;
            this->x_vel = 0;
            this->y_vel = 0;
        }

        if(event.key.scancode == sf::Keyboard::Scan::Up && this->side == 1 && !moveDown) {
            this->moveUp = false;
            this->moveDown = false;
            this->x_vel = 0;
            this->y_vel = 0;
        }

        if(event.key.scancode == sf::Keyboard::Scan::Down && this->side == 1 && !moveUp) {
            this->moveUp = false;
            this->moveDown = false;
            this->x_vel = 0;
            this->y_vel = 0;
        }
    }

    paddleEvent.x_vel = this->x_vel;
    paddleEvent.y_vel = this->y_vel;

    if(moveUp) {
        if(this->paddleShape.getPosition().y < 0)
            return;
        this->y_vel = -.25;
        this->paddleShape.move(x_vel, y_vel);
    } else if(moveDown) {
        if(this->paddleShape.getPosition().y + PADDLE_HEIGHT > SCREEN_HEIGHT)
            return;
        this->y_vel = .25;
        this->paddleShape.move(x_vel, y_vel);
    }

    paddleEvent.x_vel = this->x_vel;
    paddleEvent.y_vel = this->y_vel;
}

void Paddle::update(float y_vel) {
    if(this->paddleShape.getPosition().y <= 0 && y_vel < 0)
        return;
    if(this->paddleShape.getPosition().y + PADDLE_HEIGHT >= SCREEN_HEIGHT && y_vel > 0)
        return;
    this->paddleShape.move(0, y_vel);
}

void Paddle::render(sf::RenderTarget& target) {
    target.draw(paddleShape);
}
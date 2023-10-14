#pragma once

#include <SFML/Graphics.hpp>

#include "Net.h"

#include "Paddle.h"
#include "Ball.h"

class Game {
    sf::RenderWindow* window;
    Paddle* leftPaddle = new Paddle(0);
    Paddle* rightPaddle = new Paddle(1);
    Ball ball;

    PaddleEvent paddleEvent;

    Net* myNet;
    std::vector<unsigned> neuralNetTopology;
    std::vector<double> inputVals;
    std::vector<double> targetVals;
    std::vector<double> resultVals;
public:
    Game();

    void initWindow();

    void updateDt();
    void update(sf::Event&);
    void render();
    void run();
};
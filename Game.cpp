#include <iostream>

#include "Net.h"

#include "Global.h"
#include "Game.h"

Game::Game() : paddleEvent(0, 0){
    initWindow();
    neuralNetTopology.clear();
    neuralNetTopology.push_back(2);
    neuralNetTopology.push_back(4);
    neuralNetTopology.push_back(1);

    myNet = new Net(neuralNetTopology);
}

void Game::initWindow() {
    this->window = new sf::RenderWindow();
    this->window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong", sf::Style::Titlebar | sf::Style::Close);
}

void Game::update(sf::Event& event) {
    ball.update(*leftPaddle, *rightPaddle);

    inputVals.clear();
    targetVals.clear();

    inputVals.push_back(ball.getPosition().x);
    inputVals.push_back(ball.getPosition().y);
    targetVals.push_back(ball.getPosition().y < rightPaddle->getPosition().y ? 0 : 1);

    leftPaddle->update(event, paddleEvent);

    myNet->feedForward(inputVals);
    myNet->backProp(targetVals);
    myNet->getResults(resultVals);

    //leftPaddle->update(resultVals[0] < .5 ? -.25 : .25);
    rightPaddle->update(resultVals[0] < .5 ? -.25 : .25);

    /*std::cout << std::endl;
    std::cout << "Inputs: " << inputVals[0] << " " << inputVals[1] << std::endl;
    std::cout << "Outputs: " << resultVals[0] << std::endl;
    std::cout << "Targets: " << targetVals[0] << std::endl;*/
}

void Game::render() {
    this->window->clear();

    leftPaddle->render(*this->window);
    rightPaddle->render(*this->window);
    ball.render(*this->window);
    this->window->display();
}

void Game::run() {
    while (this->window->isOpen()) {
        sf::Event event;
        while (this->window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window->close();
        }

        update(event);
        render();
    }
}
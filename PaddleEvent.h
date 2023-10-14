#pragma once

struct PaddleEvent {
    float x_vel = 0;
    float y_vel = 0;

    PaddleEvent(float, float);
    ~PaddleEvent();
};
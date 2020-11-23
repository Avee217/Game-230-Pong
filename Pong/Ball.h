#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
    Vector2f position;
    CircleShape ballShape;

    float xVelocity = 100.0f;
    float yVelocity = 0.0f;
    float width = 10.0f;
    float height = 10.0f;
   

public:
    Ball(float startX, float startY);

    FloatRect getPosition();
    float getPositionRight();
    float getPositionBottom();

    CircleShape getShape();

    float getXVelocity();

    void reboundTopOrBottom(FloatRect lastBallPosition, FloatRect currentBallPosition);

    void reboundPaddleLeft(float paddleY, float paddleHeight);
    void reboundPaddleRight(float paddleY, float paddleHeight);

    void hitOut(float check);

    void update(float timeElapsed);
    void reset(float startX, float startY);

};

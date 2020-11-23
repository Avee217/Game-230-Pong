#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
    Vector2f position;

    // A RectangleShape object called ref
    RectangleShape ballShape;

    float xVelocity = 300.0f;
    float yVelocity = 20.0f;
    float width = 10.0f;
    float height = 10.0f;
   

public:
    Ball(float startX, float startY);

    FloatRect getPosition();
    float getPositionRight();
    float getPositionBottom();

    RectangleShape getShape();//circle shape

    float getXVelocity();

    void reboundTopOrBottom(FloatRect lastBallPosition, FloatRect currentBallPosition);

    void reboundPaddle(float paddleY, float paddleHeight, int No);

    void hitOut();

    void update(float timeElapsed);
    void reset(float startX, float startY);

};

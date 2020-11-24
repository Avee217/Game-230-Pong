#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Paddle
{
private:
    Vector2f position;
    float paddleHeight;
    float paddleWidth;
    RectangleShape paddleShape;

    float paddleSpeed = 300.0f;

public:
    Paddle(float startX, float startY);

    void setSpeed(float speed);

    FloatRect getPosition();
    void changePosition(float newX, float newY);
    void changeSize(float width, float height);

    RectangleShape getShape();

    void moveUp(float timeElapsed,float limitChange);

    void moveDown(float timeElapsed,float limitChange);

    void update(float timeElapsed);
    void reset(float startX, float startY);
    int aiMove(FloatRect ballPosition);

};




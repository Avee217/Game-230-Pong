#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Paddle
{
protected:
    Vector2f position;
    float paddleHeight;
    float paddleWidth;

    // A RectangleShape object
    RectangleShape paddleShape;

    float paddleSpeed = 300.0f;

public:
    Paddle(float startX, float startY);

    void setSpeed(float speed);

    FloatRect getPosition();

    RectangleShape getShape();

    void moveUp(float timeElapsed);//move up

    void moveDown(float timeElapsed);//move down

    void update(float timeElapsed);
    void reset(float startX, float startY);

};

class AIPaddle : public Paddle

{
public:
    AIPaddle(float startX, float startY);

    int aiMove(FloatRect ballPosition );


};


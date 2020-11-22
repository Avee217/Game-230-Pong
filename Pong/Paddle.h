#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Paddle
{
private:
    Vector2f position;

    // A RectangleShape object
    RectangleShape paddleShape;

    float paddleSpeed = .3f;

public:
    Paddle(float startX, float startY);

    FloatRect getPosition();

    RectangleShape getShape();

    void moveLeft();//move up

    void moveRight();//move down

    void update();

};



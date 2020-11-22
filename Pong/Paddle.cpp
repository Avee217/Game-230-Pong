//#include "stdafx.h"
#include "Paddle.h"

// This is the constructor and it is called when we create an object
Paddle::Paddle(float startX, float startY)
{
    position.x = startX;
    position.y = startY;

    paddleShape.setSize(sf::Vector2f(50, 5));
    paddleShape.setPosition(position);
}

FloatRect Paddle::getPosition()
{
    return paddleShape.getGlobalBounds();
}

RectangleShape Paddle::getShape()
{
    return paddleShape;
}

//change to .y for up and down
void Paddle::moveLeft()
{
    position.x -= paddleSpeed;
}

void Paddle::moveRight()
{
    position.x += paddleSpeed;
}

void Paddle::update()
{
    paddleShape.setPosition(position);
}
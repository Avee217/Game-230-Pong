#include "Paddle.h"

Paddle::Paddle(float startX, float startY)
{
    
    paddleHeight = 100;
    paddleWidth = 5;
    position.x = startX;
    position.y = startY-paddleHeight/2.0f;
    

    paddleShape.setSize(sf::Vector2f(paddleWidth,paddleHeight));
    paddleShape.setPosition(position);
}

void Paddle::setSpeed(float speed)
{
    paddleSpeed = speed;
}

void Paddle::changePosition(float newX, float newY)
{
    position.x = newX;
    position.y = newY;
    paddleShape.setPosition(position);
}

void Paddle::changeSize(float width, float height) 
{
    paddleWidth = width;
    paddleHeight = height;
    paddleShape.setSize(sf::Vector2f(paddleWidth, paddleHeight));
}

FloatRect Paddle::getPosition()
{
    return paddleShape.getGlobalBounds();
}

RectangleShape Paddle::getShape()
{
    return paddleShape;
}

void Paddle::moveUp(float timeElapsed, float limitChange)
{
    if (position.y >= (0+limitChange))
        position.y -= paddleSpeed * timeElapsed;
    
}

void Paddle::moveDown(float timeElapsed, float limitChange)
{
    if (position.y <= (600-paddleHeight-limitChange))
    position.y += paddleSpeed * timeElapsed;
}

void Paddle::update(float timeElapsed)
{
    paddleShape.setPosition(position);
}

void Paddle::reset(float startX, float startY)
{
    position.x = startX;
    position.y = startY - paddleHeight / 2.0f;
}


int Paddle::aiMove(FloatRect ballPosition) {
    if (ballPosition.top > getPosition().top + paddleHeight)
    {
        return 1;
    }
    if (ballPosition.top < getPosition().top)
    {
        return -1;
    }
    return 0;
}


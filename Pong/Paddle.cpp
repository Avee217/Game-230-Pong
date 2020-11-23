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

FloatRect Paddle::getPosition()
{
    return paddleShape.getGlobalBounds();
}

RectangleShape Paddle::getShape()
{
    return paddleShape;
}

void Paddle::moveUp(float timeElapsed)
{
    if (position.y >= (0))
        position.y -= paddleSpeed * timeElapsed;
    
}

void Paddle::moveDown(float timeElapsed)
{
    if (position.y <= (600-paddleHeight))
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

AIPaddle::AIPaddle(float startX, float startY):Paddle(startX, startY)
{
    setSpeed(100.0f);
}

int AIPaddle::aiMove(FloatRect ballPosition) {
    if (ballPosition.top> getPosition().top + paddleHeight)
    {
        return 1;
    }
    if (ballPosition.top < getPosition().top)
    {
        return -1;
    }
    return 0;
}
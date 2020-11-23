//#include "stdafx.h"
#include "Ball.h"

// This the constructor and it is called when we create an object
Ball::Ball(float startX, float startY)
{
    position.x = startX;
    position.y = startY;
    

    ballShape.setSize(sf::Vector2f(width, height));
    ballShape.setPosition(position);
}

FloatRect Ball::getPosition()
{
    return ballShape.getGlobalBounds();
}
float Ball::getPositionRight()
{
    return ballShape.getGlobalBounds().left + width;
}
float Ball::getPositionBottom()
{
    return ballShape.getGlobalBounds().top + height;
}

RectangleShape Ball::getShape()
{
    return ballShape;
}

float Ball::getXVelocity()
{
    return xVelocity;
}

void Ball::reboundTopOrBottom(FloatRect lastBallPosition, FloatRect currentBallPosition )
{
    yVelocity = -yVelocity;
}

void Ball::reboundPaddle(float paddleY, float paddleHeight,int No)
{
   /* position.x -= (xVelocity * 30);
    xVelocity = -xVelocity;*/

    float paddleHit = (position.y - paddleY)/ (paddleHeight / 2.0f); // position on the paddle the ball hits

    xVelocity = abs(xVelocity + xVelocity * (1.0f - abs(paddleHit)) * 0.1f - abs(xVelocity * paddleHit * -.2f));
    yVelocity = yVelocity + abs(yVelocity) * paddleHit * .5f;
    if (xVelocity > 300)
        xVelocity = 300;
    xVelocity = No * xVelocity;
    
}

void Ball::hitOut()
{
    position.y = 300;
    position.x = 400;
    xVelocity = 300.0f;
    yVelocity = 20.0f;

}

void Ball::update(float timeElapsed)
{
    // Update the ball position variables
    position.y += yVelocity*timeElapsed;
    position.x += xVelocity*timeElapsed;

    // Move the ball and the paddle
    ballShape.setPosition(position);
}

void Ball::reset(float startX, float startY)
{
    position.x = startX;
    position.y = startY;
    xVelocity = 300.0f;
    yVelocity = 20.0f;
}
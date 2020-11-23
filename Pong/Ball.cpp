#include "Ball.h"

Ball::Ball(float startX, float startY)
{
    position.x = startX;
    position.y = startY;
    

    ballShape.setRadius(5);
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

CircleShape Ball::getShape()
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

void Ball::reboundPaddleLeft(float paddleY, float paddleHeight)
{
   position.x -= (xVelocity/30);
   
   float paddleHitPos = (position.y - paddleY) / (paddleHeight/2);
   xVelocity = abs(xVelocity) + 50;
    if (xVelocity > 500) xVelocity = 500;
   yVelocity = -100* (1.0f-paddleHitPos );
}
void Ball::reboundPaddleRight(float paddleY, float paddleHeight)
{
    //position.x -= (xVelocity / 30);
    
    float paddleHitPos = (position.y - paddleY) / (paddleHeight / 2);
    xVelocity = abs(xVelocity) + 50;
    if (xVelocity > 500) xVelocity = 500;
    xVelocity = -xVelocity;
    yVelocity = -100 * (1.0f-paddleHitPos);
}

void Ball::hitOut(float check)
{
    position.y = 300;
    position.x = 400;
    xVelocity = check*100.0f;
    yVelocity = 0.0f;

}

void Ball::update(float timeElapsed)
{
    // Update the ball position variables
    position.y += yVelocity*timeElapsed;
    position.x += xVelocity*timeElapsed;

    ballShape.setPosition(position);

}

void Ball::reset(float startX, float startY)
{
    position.x = startX;
    position.y = startY;
    xVelocity = 100.0f;
    yVelocity = 0.0f;
}
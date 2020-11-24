#include "Obstacle.h"
#include<math.h>

Obstacle::Obstacle(float startX, float startY)
{

    obstacleHeight = 75;
    obstacleWidth = 5;
    position.x = startX;
    position.y = startY;


    obstacleShape.setSize(sf::Vector2f(obstacleWidth, obstacleHeight));
    obstacleShape.setPosition(position);
}

void Obstacle::setSpeed(float speed)
{
    obstacleSpeed = speed;
}
void Obstacle::changeSize(float width, float height)
{
    obstacleWidth = width;
    obstacleHeight = height;
    obstacleShape.setSize(sf::Vector2f(obstacleWidth, obstacleHeight));
}

FloatRect Obstacle::getPosition()
{
    return obstacleShape.getGlobalBounds();
}

RectangleShape Obstacle::getShape()
{
    return obstacleShape;
}

float Obstacle::getPositionBottom() {
   return obstacleShape.getGlobalBounds().top + sqrt(obstacleWidth*obstacleWidth+obstacleHeight*obstacleHeight);
}

void Obstacle::reboundTopOrBottom()
{
    obstacleSpeed = -obstacleSpeed;
}

void Obstacle::update(float timeElapsed)
{
    position.y += obstacleSpeed * timeElapsed;
    obstacleShape.setPosition(position);
}

void Obstacle::reset(float startX, float startY)
{
    position.x = startX;
    position.y = startY;
}
void Obstacle::rotation(float rotation)
{
   obstacleShape.setRotation(rotation);
}

#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Obstacle
{
private:
    Vector2f position;
    float obstacleHeight;
    float obstacleWidth;
    RectangleShape obstacleShape;

    float obstacleSpeed = 100.0f;
public:

    Obstacle(float startX, float startY);

    void setSpeed(float speed);
    
    void reboundTopOrBottom();
    float getPositionBottom();

    FloatRect getPosition();

    void rotation(float rotation);
    
    void changeSize(float width, float height);

    RectangleShape getShape();
    
    void update(float timeElapsed);
    void reset(float startX, float startY);
   
};


//#include "stdafx.h"
#include "Paddle.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

// This is where our game starts from
int main()
{
    int windowWidth = 800;
    int windowHeight = 600;
    // Make a window that is 800 by 600 pixels
    // And has the title "Pong!"
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong!");

    //Needs a change
    int score = 0;
    int lives = 3;

    // create a paddle
    Paddle paddle(windowWidth / 2, windowHeight - 20);

    // create a ball
    Ball ball(windowWidth / 2, 1);

    // Create a "Text" object called "message"
    Text hud;

    //Font from dafont.com
    Font font;
    font.loadFromFile("DS-DIGIT.ttf");

    // Set the font to our message
    hud.setFont(font);

    // Make it really big
    hud.setCharacterSize(75);

    // Choose a color
    hud.setFillColor(sf::Color::White);

    // This "while" loop goes round and round- perhaps forever
    while (window.isOpen())
    {
        // Handle Player Input

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                //the window is closing - bye
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            // move left...
            paddle.moveLeft();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            // move right...
            paddle.moveRight();
        }
        else if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            // quit...
            // the window is closing - bye
            window.close();
        }
        // Update the frames

        // Handle ball hitting the bottom
        //Cange this function
        if (ball.getPosition().top > windowHeight)
        {
            // reverse the ball direction
            ball.hitBottom();

            // Remove a life
            lives--;

            // Check for zero lives
            if (lives < 1) {
                // reset the score
                score = 0;
                // reset the lives
                lives = 3;
            }

        }

        // Handle ball hitting top
        if (ball.getPosition().top < 0)
        {
            ball.reboundPaddleOrTop();

            // Add a point to the players score
            score++;

        }

        // Handle ball hitting sides
        // swap for pong
        //seperate them too
        if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth)
        {
            ball.reboundSides();
        }

        // Has the ball hit the Paddle?
        if (ball.getPosition().intersects(paddle.getPosition()))
        {
            // Hit detected so reverse the ball and score a point
            ball.reboundPaddleOrTop();
        }

        ball.update();
        paddle.update();

        // Update the HUD text
        std::stringstream ss;
        ss << "Score:" << score << "    Lives:" << lives;
        hud.setString(ss.str());


        //Draw the Frame
        // Clear everything from the last frame
        window.clear(Color(26, 128, 182, 255));
 
        window.draw(paddle.getShape());

        window.draw(ball.getShape());

        // Draw our score
        window.draw(hud);

        // Show everything we just drew
        window.display();
    }// This is the end of the "while" loop

    return 0;
}

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
#include<chrono>

using namespace sf;
// This is where our game starts from
int scoreOne = 0;
int scoreTwo = 0;

void reset()
{
	scoreOne = 0;
	scoreTwo = 0;
	
}
int main()
{
	int windowWidth = 800;
	int windowHeight = 600;
	std::chrono::steady_clock::time_point clockStart = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point clockEnd = std::chrono::steady_clock::now();
	float timeElapsed;
	// Make a window that is 800 by 600 pixels
	// And has the title "Pong!"
	RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong!");
	window.setFramerateLimit(30);

	//Needs a change

	int paddleCheck = 0;
	bool pause = false;
	bool resetgame = false;
	int aiMoveChoice = 0;
	FloatRect lastBallPosition, currentBallPosition;
	
	SoundBuffer buffer;
	buffer.loadFromFile("Sounds/Bump.wav");
	Sound bump(buffer);

	Texture texture;
	texture.loadFromFile("Images/pong.png");
	Sprite s(texture);

	// create a paddle
	Paddle paddleOne(20.0f, windowHeight / 2.0f);

	AIPaddle paddleTwo(windowWidth - 20.0f, windowHeight / 2.0f);
	//Paddle paddleTwo(windowWidth - 20, windowHeight / 2);

	// create a ball
	Ball ball(windowWidth / 2.0f, windowHeight / 2.0f);
	lastBallPosition = ball.getPosition();

	// Create a "Text" object called "message"
	Text hud;

	//Font from dafont.com
	Font font;
	font.loadFromFile("Font/DS-DIGIT.ttf");

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

		clockEnd = std::chrono::steady_clock::now();
		timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(clockEnd - clockStart).count() / 1000000.0;
		clockStart = clockEnd;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				//the window is closing - bye
				window.close();
		}

		currentBallPosition = ball.getPosition();

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			// move left paddle up
			paddleOne.moveUp(timeElapsed);
		}


		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			// move left paddle down
			paddleOne.moveDown(timeElapsed);
		}


		aiMoveChoice = paddleTwo.aiMove(ball.getPosition());
		if (aiMoveChoice > 0)
		{
			paddleTwo.moveDown(timeElapsed);

		}
		if (aiMoveChoice < 0)
		{
			paddleTwo.moveUp(timeElapsed);
		}

		aiMoveChoice = 0;

		//if (Keyboard::isKeyPressed(Keyboard::I))
		//{
		//    // move right paddle up
		//    paddleTwo.moveUp();
		//}
		//else if (Keyboard::isKeyPressed(Keyboard::K))
		//{
		//    // move right paddle down
		//    paddleTwo.moveDown();
		//}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			// quit...
			// the window is closing - bye
			window.close();
		}

		
		if (Keyboard::isKeyPressed(Keyboard::P))
		{
			pause = !pause;
		}
		
		if (resetgame) 
		{
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				resetgame = false;
				reset();
				paddleOne.reset(20.0f, windowHeight / 2.0f);
				paddleTwo.reset(windowWidth - 20.0f, windowHeight / 2.0f);
				ball.reset(windowWidth / 2.0f, windowHeight + 20 / 2.0f); 

			}
		}
		
		// Update the frames

		// Handle ball hitting the bottom
		//Cange this function
	   /* if (ball.getPosition().top > windowHeight)
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

		}*/


		if (ball.getPosition().left <= 0)
		{
			// reverse the ball direction
			ball.hitOut();
			if (paddleCheck == 1) scoreOne++;
			if (paddleCheck == 2) scoreTwo++;



		}

		if (ball.getPositionRight() >= windowWidth)
		{
			// reverse the ball direction
			ball.hitOut();
			if (paddleCheck == 1) scoreOne++;
			if (paddleCheck == 2) scoreTwo++;



		}



		// Handle ball hitting top
		if (ball.getPosition().top < 0 || ball.getPositionBottom()>windowHeight)
		{
			ball.reboundTopOrBottom(lastBallPosition, currentBallPosition);
			bump.play();


		}

		// Has the ball hit the Paddle?
		if (ball.getPosition().intersects(paddleOne.getPosition()))
		{
			// Hit detected so reverse the ball and score a point
			ball.reboundPaddle(paddleOne.getPosition().top, paddleOne.getPosition().height,1);
			paddleCheck = 1;
			bump.play();

		}
		if (ball.getPosition().intersects(paddleTwo.getPosition()))
		{
			// Hit detected so reverse the ball and score a point
			ball.reboundPaddle(paddleTwo.getPosition().top, paddleTwo.getPosition().height, -1);
			paddleCheck = 2;
			bump.play();
		}

		
		if (!pause && !resetgame)
		{
			ball.update(timeElapsed);
			paddleOne.update(timeElapsed);
			paddleTwo.update(timeElapsed);
		}

		lastBallPosition = ball.getPosition();
		// Update the HUD text
		std::stringstream ss;
		if(scoreOne<5&&scoreTwo<5) ss << "               " << scoreOne << "    " << scoreTwo;
		if (scoreOne >= 5) {
			resetgame = true;
			ss << "Player one wins  press space";
			
		}
		if (scoreTwo >= 5) {
			resetgame = true;
			ss << "Player two wins  press  space to restart";
			
		}


		hud.setString(ss.str());



		//Draw the Frame
		// Clear everything from the last frame
		window.clear(Color(26, 128, 182, 255));
		window.draw(s);

		window.draw(paddleOne.getShape());
		window.draw(paddleTwo.getShape());

		window.draw(ball.getShape());

		// Draw our score
		window.draw(hud);
		if (scoreOne >= 5 || scoreTwo >= 5)
		{

		}

		// Show everything we just drew
		window.display();
	}// This is the end of the "while" loop

	return 0;
}

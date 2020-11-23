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

int main()
{
	int windowWidth = 800;
	int windowHeight = 600;

	int scoreOne = 0;
	int scoreTwo = 0;

	std::chrono::steady_clock::time_point clockStart = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point clockEnd = std::chrono::steady_clock::now();
	float timeElapsed;
	// Make a window that is 800 by 600 pixels
	// And has the title "Pong!"
	RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong!");
	window.setFramerateLimit(30);

	int paddleCheck = 0;
	bool pause = false;
	bool resetgame = false;
	int aiMoveChoice = 0;
	FloatRect lastBallPosition, currentBallPosition;
	
	// Load sound file
	SoundBuffer buffer;
	buffer.loadFromFile("Sounds/Bump.wav");
	Sound bump(buffer);

	// Load backgound
	Texture texture;
	texture.loadFromFile("Images/pong.png");
	Sprite	 s(texture);
	
	// create a paddle
	Paddle paddleOne(20.0f, windowHeight / 2.0f);

	// Create AI paddle
	AIPaddle paddleTwo(windowWidth-20.0f, windowHeight / 2.0f);
	//Paddle paddleTwo(windowWidth - 20, windowHeight / 2);

	// create a ball
	Ball ball(windowWidth / 2.0f, windowHeight / 2.0f);
	lastBallPosition = ball.getPosition();

	// Create a HUD
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
		timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(clockEnd - clockStart).count() / 1000000.0f;
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

		// AI paddle movements
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
		//    paddleTwo.moveUp(timeElapsed);
		//}
		//else if (Keyboard::isKeyPressed(Keyboard::K))
		//{
		//    // move right paddle down
		//    paddleTwo.moveDown(timeElapsed);
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
				scoreOne = 0;
				scoreTwo = 0;
				paddleOne.reset(20.0f, windowHeight / 2.0f);
				paddleTwo.reset(windowWidth - 20.0f, windowHeight / 2.0f);
				ball.reset(windowWidth / 2.0f, windowHeight / 2.0f); 
				resetgame = false;

			}
		}
		
		// Update the frames

		


		if (ball.getPosition().left <= 0)
		{
			// reverse the ball direction and incease score
			ball.hitOut(-1.0f);
			scoreTwo++;
		}

		if (ball.getPositionRight() >= windowWidth)
		{
			// reverse the ball direction and increase score
			ball.hitOut(1.0f);
			scoreOne++;
		}



		// Handle ball hitting top and bottom
		if (ball.getPosition().top < 0 || ball.getPositionBottom()>windowHeight)
		{
			ball.reboundTopOrBottom(lastBallPosition, currentBallPosition);
			bump.play();
		}

		// Has the ball hit the left Paddle?

		if (ball.getPosition().intersects(paddleOne.getPosition()))
		{
					// Hit detected so reverse the ball and play sound
			ball.reboundPaddleLeft(paddleOne.getPosition().top, paddleOne.getPosition().height);
			bump.play();

		}
		
		// Has the ball hit the rgight paddle?
		if (ball.getPosition().intersects(paddleTwo.getPosition()))
		{
			// Hit detected so reverse the ball and play a sound
			ball.reboundPaddleRight(paddleTwo.getPosition().top, paddleTwo.getPosition().height);
			bump.play();
		}

		
		if (!pause && !resetgame)
		{
			
			paddleOne.update(timeElapsed);
			paddleTwo.update(timeElapsed);
			ball.update(timeElapsed);
		}

		lastBallPosition = ball.getPosition();
		// Update the HUD text
		std::stringstream ss;
		if(scoreOne<5&&scoreTwo<5) ss << "                  " << scoreOne << "    " << scoreTwo;

		if (scoreOne >= 5) {
			resetgame = true;
			ss << "  Player one wins \n space to reast";
			
		}
		if (scoreTwo >= 5) {
			resetgame = true;
			ss << "   Player two wins  \n press space to restart";
			
		}


		hud.setString(ss.str());



		//Draw the Frame
		// Clear everything from the last frame
		window.clear(Color(26, 128, 182, 255));
		window.draw(s);
		window.draw(paddleOne.getShape());
		window.draw(paddleTwo.getShape());

		window.draw(ball.getShape());

		// Draw our HUD
		window.draw(hud);

		// Show everything we just drew
		window.display();
	}// This is the end of the "while" loop

	return 0;
}

#include "Paddle.h"
#include "Ball.h"
#include"Menu.h"
#include <sstream>
#include<iostream>
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

int playerCount = 1;



int main()
{
	int windowWidth = 800;
	int windowHeight = 600;

	int scoreOne = 0;
	int scoreTwo = 0;

	playerCount = 1;

	std::chrono::steady_clock::time_point clockStart = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point clockEnd = std::chrono::steady_clock::now();
	float timeElapsed;



	// Make a window that is 800 by 600 pixels
	// And has the title "Pong!"
	RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong!");
	window.setFramerateLimit(30);// set FPS limit

	Menu menu(windowWidth,windowHeight);
	
	//bool for game states
	bool gameRunning = false;
	bool pause = false;
	bool resetGame = false;
	bool vm = false;
	int aiMoveChoice = 0;
	FloatRect lastBallPosition, currentBallPosition;

	// Load sound file 
	//Sounds from freesound.org
	SoundBuffer bumpBuffer;
	if (!bumpBuffer.loadFromFile("Sounds/Bump.wav")) {
		std::cout << "Bump Sound Error" << std::endl;
	}
	Sound bump(bumpBuffer);
	bump.setVolume(50);
	
	SoundBuffer scoreBuffer;
	if (!scoreBuffer.loadFromFile("Sounds/Score.wav")) {
		std::cout << "Score Sound Error" << std::endl;
	}
	Sound score(scoreBuffer);
	score.setVolume(50);

	// Music
	Music backgroundMusic;
	if (!backgroundMusic.openFromFile("Music/BackgroundMusic.wav")) {
		std::cout << "Background Music Error" << std::endl;
	}
	backgroundMusic.setVolume(25);

	
	Music menuMusic;
	if (!menuMusic.openFromFile("Music/MenuMusic.wav")) {
		std::cout << "Menu Music Error" << std::endl;
	}
	menuMusic.setVolume(25);

	Music victoryMusic;
	if (!victoryMusic.openFromFile("Music/VictoryMusic.wav")) {
		std::cout << "Menu Music Error" << std::endl;
	}
	victoryMusic.setVolume(25);
	

	// Load backgound
	Texture texture1;
	if (!texture1.loadFromFile("Images/pong1.png")) {
		std::cout << "background Image Error" << std::endl;
	}
	Sprite	 background,menuBackGround;
	background.setTexture(texture1);


	Texture texture2;
	if (!texture2.loadFromFile("Images/pong.png")) {
		std::cout << "background 2 Image Error" << std::endl;
	}
	menuBackGround.setTexture(texture2);
	// create a paddle
	Paddle paddleOne(20.0f, windowHeight / 2.0f); 
	Paddle paddleTwo(windowWidth - 25.0f, windowHeight / 2.0f);
	Paddle paddleA(20.0f, windowHeight / 1.25f);
	Paddle paddleB(windowWidth - 25.0f, windowHeight / 1.25f);

	// create a ball
	Ball ball(windowWidth / 2.0f, windowHeight / 2.0f);
	lastBallPosition = ball.getPosition();

	// Create a HUD
	Text hud;

	//Font from dafont.com
	Font font;
	if (!font.loadFromFile("Font/DS-DIGIT.ttf")) {
		std::cout << "Font Error" << std::endl;
	}

	// Set the font to our message
	hud.setFont(font);

	// Make it really big
	hud.setCharacterSize(50);

	// Choose a color
	hud.setFillColor(sf::Color::White);
	hud.setPosition((windowWidth / 2.0f)-40, 20);


	menuMusic.play();
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
			if (!gameRunning) {
				
				switch (event.type)
				{
				case Event::KeyReleased:
					switch (event.key.code)
					{
					case Keyboard::Up:
						menu.MoveUp();
						break;

					case Keyboard::Down:
						menu.MoveDown();
						break;

					case Keyboard::Return:
						switch (menu.GetPressedItem())
						{
						case 0:
							std::cout << "Single player has been pressed" << std::endl;
							playerCount = 1;
							gameRunning = true;
							menuMusic.stop();
							backgroundMusic.play();
							backgroundMusic.setVolume(50);
							break;
						case 1:
							std::cout << "Two-Player button has been pressed" << std::endl;
							playerCount = 2;
							gameRunning = true;
							menuMusic.stop();
							backgroundMusic.play();
							backgroundMusic.setVolume(50);
							
							break;
						case 2:
							std::cout << "Four-Player button has been pressed" << std::endl;
							playerCount = 4;
							if (playerCount == 4)
							{
								paddleOne.changePosition(20.0f, windowHeight / 4.0f);
								paddleOne.changeSize(5, 50);
								paddleTwo.changePosition(windowWidth - 25.0f, windowHeight / 4.0f);
								paddleTwo.changeSize(5, 50);
								paddleA.changeSize(5, 50);
								paddleB.changeSize(5, 50);
							}
							gameRunning = true;
							menuMusic.stop();
							backgroundMusic.play();
							backgroundMusic.setVolume(50);
							break;
						case 3:
							window.close();
							break;
						}

						break;
					}

					break;
				case Event::Closed:
					window.close();

					break;

				}

			}
		}

		if (gameRunning)
		{


			if (event.type == Event::Closed) window.close();

			currentBallPosition = ball.getPosition();

			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				// move left paddle up
				paddleOne.moveUp(timeElapsed,0.0f);
			}


			else if (Keyboard::isKeyPressed(Keyboard::S))
			{
				// move left paddle down
				if (playerCount == 4)
				{
					paddleOne.moveDown(timeElapsed, 300.0f);
				}
				else
				{
					paddleOne.moveDown(timeElapsed, 0.0f);
				}
			}

			// AI paddle movements
			if (playerCount == 1) 
			{
				aiMoveChoice = paddleTwo.aiMove(ball.getPosition());
				if (aiMoveChoice > 0)
				{
					paddleTwo.moveDown(timeElapsed,0.0f);

				}
				if (aiMoveChoice < 0)
				{
					paddleTwo.moveUp(timeElapsed,0.0f);
				}

				aiMoveChoice = 0;
			}
			if (playerCount == 2 || playerCount==4)
			{
			
				if (Keyboard::isKeyPressed(Keyboard::I))
				{
					// move right paddle up
					paddleTwo.moveUp(timeElapsed,0.0f);
				}
				else if (Keyboard::isKeyPressed(Keyboard::K))
				{
					// move right paddle down
					if (playerCount == 4)
					{
						paddleTwo.moveDown(timeElapsed, 300.0f);
					}
					else
					{
						paddleTwo.moveDown(timeElapsed, 0.0f);
					}
				}
			}
			if (playerCount == 4)
			{
				if (Keyboard::isKeyPressed(Keyboard::R))
				{
					// move right paddle up
					paddleA.moveUp(timeElapsed,325.0f);
				}
				else if (Keyboard::isKeyPressed(Keyboard::F))
				{
					// move right paddle down
					paddleA.moveDown(timeElapsed,0.0f);
				}
				if (Keyboard::isKeyPressed(Keyboard::Y))
				{
					// move right paddle up
					paddleB.moveUp(timeElapsed, 325.0f);
				}
				else if (Keyboard::isKeyPressed(Keyboard::H))
				{
					// move right paddle down
					paddleB.moveDown(timeElapsed, 0.0f);
				}

			}
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

			if (resetGame)
			{
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					scoreOne = 0;
					scoreTwo = 0;
					resetGame = false;
					vm = false;
					victoryMusic.stop();
					paddleOne.reset(20.0f, windowHeight / 2.0f);
					paddleTwo.reset(windowWidth - 25.0f, windowHeight / 2.0f);
					if (playerCount == 4) {
						paddleOne.reset(20.0f, windowHeight / 4.0f);
						paddleTwo.reset(windowWidth - 25.0f, windowHeight / 4.0f);
						Paddle paddleA(20.0f, windowHeight / 1.5f);
						Paddle paddleB(windowWidth - 25.0f, windowHeight / 1.5f);
					}
					ball.reset(windowWidth / 2.0f, windowHeight / 2.0f);
					hud.setPosition((windowWidth / 2.0f) - 40, 20);
					background.setColor(sf::Color(255, 255, 255, 255));
					backgroundMusic.play();

					

				}
			}

			// Update the frames




			if (ball.getPosition().left <= 0)
			{
				// reverse the ball direction and incease score
				ball.hitOut(-1.0f);
				score.play();
				scoreTwo++;
			}

			if (ball.getPositionRight() >= windowWidth)
			{
				// reverse the ball direction and increase score
				ball.hitOut(1.0f);
				score.play();
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

			if (playerCount == 4) 
			{
				if (ball.getPosition().intersects(paddleA.getPosition()))
				{
					// Hit detected so reverse the ball and play a sound
					ball.reboundPaddleLeft(paddleA.getPosition().top, paddleA.getPosition().height);
					bump.play();
				}

				if (ball.getPosition().intersects(paddleB.getPosition()))
				{
					// Hit detected so reverse the ball and play a sound
					ball.reboundPaddleRight(paddleB.getPosition().top, paddleB.getPosition().height);
					bump.play();
				}

			}


			if (!pause && !resetGame)
			{

				paddleOne.update(timeElapsed);
				paddleTwo.update(timeElapsed);
				if (playerCount == 4)
				{
					paddleA.update(timeElapsed);
					paddleB.update(timeElapsed);
				}
				ball.update(timeElapsed);
			}

			lastBallPosition = ball.getPosition();
			// Update the HUD text
			std::stringstream ss;
			if (scoreOne < 5 && scoreTwo < 5) ss <<scoreOne << "   " << scoreTwo;

			if (scoreOne >= 5) {
				resetGame = true;
				ss << "Left side wins \n space to reast";
				hud.setPosition(windowWidth / 2 - 250, windowHeight/2);
				backgroundMusic.stop();
				if (!vm) 
				{
					victoryMusic.play();
					victoryMusic.setVolume(50);
				}
				vm = true;
				background.setColor(sf::Color(255,0,0,255));

			}
			if (scoreTwo >= 5) {
				resetGame = true;
				ss << "Right Side wins  \n press space to restart";
				hud.setPosition(windowWidth / 2 - 250, windowHeight/2);
				backgroundMusic.stop();
				if(!vm)
				{
					victoryMusic.play();
					victoryMusic.setVolume(50);
				}
				vm = true;
				background.setColor(sf::Color(0,0,255,255));
			}


			hud.setString(ss.str());



			//Draw the Frame
			// Clear everything from the last frame
			window.clear(Color(26, 128, 182, 255));
			window.draw(background);
			if (!resetGame)
			{
				if (playerCount == 1 || playerCount == 2)
				{
					window.draw(paddleOne.getShape());
					window.draw(paddleTwo.getShape());
				}
				//if (playerCount == 1) window.draw(paddleAI.getShape());
				//if (playerCount == 2) window.draw(paddleTwo.getShape());
				if (playerCount == 4)
				{
					window.draw(paddleOne.getShape());
					window.draw(paddleTwo.getShape());
					window.draw(paddleA.getShape());
					window.draw(paddleB.getShape());
				}

				window.draw(ball.getShape());
			}

			// Draw our HUD
			window.draw(hud);

			// Show everything we just drew
			window.display();
		}
		if (!gameRunning)
		{

			window.clear();
			window.draw(menuBackGround);

			menu.draw(window);

			window.display();
		}
	}// This is the end of the "while" loop
	return 0;
}

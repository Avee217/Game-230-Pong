#include "Paddle.h"
#include "Ball.h"
#include"Menu.h"
#include"Obstacle.h"
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

int main()
{
	float windowWidth = 800;
	float windowHeight = 600;

	int scoreOne = 0;
	int scoreTwo = 0;
	int playerCount = 1;

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
	Paddle paddleOne(20.0f, windowHeight * 0.5f); 
	Paddle paddleTwo(windowWidth - 25.0f, windowHeight * 0.5f);
	Paddle paddleA(20.0f, windowHeight * 0.75f);
	Paddle paddleB(windowWidth - 25.0f, windowHeight * 0.75f);

	Obstacle obstacle(windowWidth * 0.25f, windowHeight * 0.75f);
	//obstacle.changeSize(50, 50);
	//obstacle.rotation(45.0f);

	Obstacle obstacle2(windowWidth * 0.75f, windowHeight * 0.25f);
	obstacle2.setSpeed(-100.0f);
	//obstacle2.changeSize(50, 50);
	//obstacle2.rotation(45.0f);
	

	// create a ball
	Ball ball(windowWidth / 2.0f, windowHeight / 2.0f);

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
	menuMusic.setLoop(true);
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
			if (!gameRunning) 
			{
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
						case 1:
							std::cout << "Single player has been pressed" << std::endl;
							playerCount = 1;
							gameRunning = true;
							paddleTwo.setSpeed(150.0f);
							menuMusic.stop();
							backgroundMusic.play();
							backgroundMusic.setLoop(true);
							backgroundMusic.setVolume(50);
							break;

						case 2:
							std::cout << "Two-Player button has been pressed" << std::endl;
							playerCount = 2;
							gameRunning = true;
							menuMusic.stop();
							backgroundMusic.play();
							backgroundMusic.setLoop(true);
							backgroundMusic.setVolume(50);
							break;

						case 3:
							std::cout << "Four-Player button has been pressed" << std::endl;
							playerCount = 4;
							if (playerCount == 4)
							{
								paddleOne.changePosition(20.0f, windowHeight * 0.25f);
								paddleOne.changeSize(5, 50);
								paddleTwo.changePosition(windowWidth - 25.0f, windowHeight *0.25f);
								paddleTwo.changeSize(5, 50);
								paddleA.changeSize(5, 50);
								paddleB.changeSize(5, 50);
							}
							gameRunning = true;
							menuMusic.stop();
							backgroundMusic.play();
							backgroundMusic.setLoop(true);
							backgroundMusic.setVolume(50);
							break;

						case 4:
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

			// Moving Paddle One
			if (Keyboard::isKeyPressed(Keyboard::W))
			{	
				paddleOne.moveUp(timeElapsed,0.0f);
			}
			else if (Keyboard::isKeyPressed(Keyboard::S))
			{
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
				if (ball.getPosition().left > windowWidth * 0.34f) 
				{
					aiMoveChoice = paddleTwo.aiMove(ball.getPosition());
					if (aiMoveChoice > 0)
					{
						paddleTwo.moveDown(timeElapsed, 0.0f);

					}
					if (aiMoveChoice < 0)
					{
						paddleTwo.moveUp(timeElapsed, 0.0f);
					}

					aiMoveChoice = 0;
				}
			}

			//Moving Paddle Two
			if (playerCount == 2 || playerCount==4)
			{
				if (Keyboard::isKeyPressed(Keyboard::I))
				{
					paddleTwo.moveUp(timeElapsed,0.0f);
				}
				else if (Keyboard::isKeyPressed(Keyboard::K))
				{
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
				//Moving Paddle A
				if (Keyboard::isKeyPressed(Keyboard::R))
				{					
					paddleA.moveUp(timeElapsed,300.0f);
				}
				else if (Keyboard::isKeyPressed(Keyboard::F))
				{					
					paddleA.moveDown(timeElapsed,0.0f);
				}

				//Moving Paddle B
				if (Keyboard::isKeyPressed(Keyboard::Y))
				{					
					paddleB.moveUp(timeElapsed, 300.0f);
				}
				else if (Keyboard::isKeyPressed(Keyboard::H))
				{					
					paddleB.moveDown(timeElapsed, 0.0f);
				}

			}

			//Exiting the game 
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				// quit...
				// the window is closing - bye
				window.close();
			}

			//Pausing
			if (Keyboard::isKeyPressed(Keyboard::P))
			{
				pause = !pause;
			}

			if (resetGame)
			{
				//Restart current game
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
					backgroundMusic.setLoop(true);
				}

				//Back to Main menu
				if (Keyboard::isKeyPressed(Keyboard::Q))
				{
					scoreOne = 0;
					scoreTwo = 0;
					victoryMusic.stop();
					gameRunning = false;
					resetGame = false;
					vm = false;
					hud.setPosition((windowWidth / 2.0f) - 40, 20);
					background.setColor(sf::Color(255, 255, 255, 255));
					menuMusic.play();
				}
				
			}

			// Collisions
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
			if (ball.getPosition().top <= 0 || ball.getPositionBottom()>=windowHeight)
			{
				ball.reboundTopOrBottom();
				bump.play();
			}
			if (obstacle.getPosition().top <= 0 || obstacle.getPositionBottom()>=windowHeight)
			{
				obstacle.reboundTopOrBottom();
				bump.play();
			}
			if (obstacle2.getPosition().top <= 0 || obstacle2.getPositionBottom()>=windowHeight)
			{
				obstacle2.reboundTopOrBottom();
				bump.play();
			}

			if (ball.getPosition().intersects(obstacle.getPosition())) 
			{
				ball.reboundObstacle(obstacle.getPosition().top, obstacle.getPosition().height);
				bump.play();
			}
			if (ball.getPosition().intersects(obstacle2.getPosition()))
			{
				ball.reboundObstacle(obstacle2.getPosition().top, obstacle2.getPosition().height);
				bump.play();
			}

			// Has the ball hit the left Paddle One?
			if (ball.getPosition().intersects(paddleOne.getPosition()))
			{
				// Hit detected so reverse the ball and play sound
				ball.reboundPaddleLeft(paddleOne.getPosition().top, paddleOne.getPosition().height);
				bump.play();
				
			}

			// Has the ball hit the rgight paddle Two?
			if (ball.getPosition().intersects(paddleTwo.getPosition()))
			{
				// Hit detected so reverse the ball and play a sound
				ball.reboundPaddleRight(paddleTwo.getPosition().top, paddleTwo.getPosition().height);
				bump.play();
			}

			if (playerCount == 4) 
			{
				// Has the ball hit the left Paddle A?
				if (ball.getPosition().intersects(paddleA.getPosition()))
				{
					// Hit detected so reverse the ball and play a sound
					ball.reboundPaddleLeft(paddleA.getPosition().top, paddleA.getPosition().height);
					bump.play();	
				}

				// Has the ball hit the left Paddle B?
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
				obstacle.update(timeElapsed);
				obstacle2.update(timeElapsed);
			}

			// Update the HUD text
			std::stringstream ss;
			if (scoreOne < 5 && scoreTwo < 5) ss <<scoreOne << "   " << scoreTwo;

			if (scoreOne >= 5) {
				resetGame = true;
				ss << "Left side wins\nspace to reast\nQ to return to Menu";
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
				ss << "Right Side wins\npress space to restart\nQ to return to Menu";
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
				
				if (playerCount == 4)
				{
					window.draw(paddleOne.getShape());
					window.draw(paddleTwo.getShape());
					window.draw(paddleA.getShape());
					window.draw(paddleB.getShape());
				}

				window.draw(ball.getShape());
				window.draw(obstacle.getShape());
				window.draw(obstacle2.getShape());
			}

			// Draw the HUD
			window.draw(hud);

			// Show everything drewn
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

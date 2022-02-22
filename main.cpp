//Author: Maria Karaszewska
//Date: 05-2021

#include "playGame.h"
#include "functions.h"
#include "leaderboard.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1292, 798), "SnakeGame", Style::Titlebar | Style::Close);
	//window.setMouseCursorVisible(false);

	Music bgMusic;
	bgMusic.openFromFile("sounds/SneakySnitchKevinMacLeod(NoCopyrightMusic).wav");
	bgMusic.setLoop(true);
	bgMusic.play();

	Image icon;
	icon.loadFromFile("images/icon.png");

	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Texture imgSnakeTex;
	imgSnakeTex.loadFromFile("images/snake.png");
	imgSnakeTex.setSmooth(true);

	Sprite imgSnake;
	imgSnake.setTexture(imgSnakeTex, true);
	imgSnake.setPosition(700, -50);
	imgSnake.setScale(1.75, 1.75);
	imgSnake.setRotation(8.5);

	Texture imgBackgroundTex;
	imgBackgroundTex.loadFromFile("images/background.jpg");

	Sprite imgBackground;
	imgBackground.setTexture(imgBackgroundTex);

	Font font;
	font.loadFromFile("fonts/Anton.ttf");

	Font titleFont;
	titleFont.loadFromFile("fonts/BoyzRGrossShadowNF.ttf");

	Text title;
	title.setFont(titleFont);
	title.setString("Voracious Snake");
	title.setCharacterSize(178);
	title.setFillColor(Color(77, 45, 14));
	title.setOutlineColor(Color::White);
	title.setOutlineThickness(5);
	title.setStyle(Text::Bold);
	title.setPosition(window.getSize().x / 2.f - title.getGlobalBounds().width / 2.f, 0);

	Text playGame;
	playGame.setFont(font);
	playGame.setString("Play Game");
	playGame.setCharacterSize(64);
	playGame.setFillColor(Color::White);
	playGame.setOutlineColor(Color(77, 45, 14));
	playGame.setOutlineThickness(3);
	playGame.setLetterSpacing(2);
	playGame.setPosition(window.getSize().x / 3.f - playGame.getGlobalBounds().width / 2.f, 285);

	Text leaderboard;
	leaderboard.setFont(font);
	leaderboard.setString("Leaderboard");
	leaderboard.setCharacterSize(64);
	leaderboard.setFillColor(Color::White);
	leaderboard.setOutlineColor(Color(77, 45, 14));
	leaderboard.setOutlineThickness(3);
	leaderboard.setLetterSpacing(2);
	leaderboard.setPosition(window.getSize().x / 3.f - leaderboard.getGlobalBounds().width / 2.f, 440);

	Text exitGame;
	exitGame.setFont(font);
	exitGame.setString("Exit Game");
	exitGame.setCharacterSize(64);
	exitGame.setFillColor(Color::White);
	exitGame.setOutlineColor(Color(77, 45, 14));
	exitGame.setOutlineThickness(3);
	exitGame.setLetterSpacing(2);
	exitGame.setPosition(window.getSize().x / 3.f - exitGame.getGlobalBounds().width / 2.f, 595);

	Text control;
	control.setFont(font);
	control.setString("Use arrows to control the game");
	control.setCharacterSize(30);
	control.setFillColor(Color::Black);
	control.setPosition(window.getSize().x / 3.f - control.getGlobalBounds().width / 2.f, 720);

	int pressCounter = -1;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
				case Event::Closed:
					window.close();
					break;

				case Event::KeyPressed:
					if (event.key.code == Keyboard::Down) {
						pressCounter += 1;

						switch (pressCounter % 3) {
							case 0:
								playGame.setFillColor(Color::Red);
								leaderboard.setFillColor(Color::White);
								exitGame.setFillColor(Color::White);
								break;
							case 1:
								playGame.setFillColor(Color::White);
								leaderboard.setFillColor(Color::Red);
								exitGame.setFillColor(Color::White);
								break;
							case 2:
								playGame.setFillColor(Color::White);
								leaderboard.setFillColor(Color::White);
								exitGame.setFillColor(Color::Red);
								break;
						}
					}

					if (event.key.code == Keyboard::Up) {
						if (playGame.getFillColor() == Color::Red) {
							playGame.setFillColor(Color::White);
							leaderboard.setFillColor(Color::White);
							exitGame.setFillColor(Color::Red);
						}
						else if (leaderboard.getFillColor() == Color::Red) {
							playGame.setFillColor(Color::Red);
							leaderboard.setFillColor(Color::White);
							exitGame.setFillColor(Color::White);
						}
						else if (exitGame.getFillColor() == Color::Red) {
							playGame.setFillColor(Color::White);
							leaderboard.setFillColor(Color::Red);
							exitGame.setFillColor(Color::White);
						}
						else {
							playGame.setFillColor(Color::Red);
							leaderboard.setFillColor(Color::White);
							exitGame.setFillColor(Color::White);
						}
					}

					if (event.key.code == Keyboard::Escape) {
						if (playGame.getFillColor() == Color::Red || leaderboard.getFillColor() == Color::Red || exitGame.getFillColor() == Color::Red) {
							playGame.setFillColor(Color::White);
							leaderboard.setFillColor(Color::White);
							exitGame.setFillColor(Color::White);
						}
						else {
							displayExitBox(font, window, icon);
						}
					}

					if (event.key.code == Keyboard::Enter) {
						if (playGame.getFillColor() == Color::Red) {
							readRanking();
							chooseLevel(window, font, imgBackground);
							extern int points;
							extern bool gameOn;

							if (gameOn) {

								extern int globalDelay;
								extern int maxScore;

								if (points > maxScore) {
									bgMusic.pause();
									newBestScore(window, imgBackground, font);
									bgMusic.play();
								}

								endGame(window, font, imgBackground, globalDelay);

								extern int key;
								if (key == 13) {

									extern int minScore;

									if (points < minScore || points == 0) {
										bgMusic.pause();
										notEnough(window, imgBackground, font);
										bgMusic.play();
									}
									else saveScore(window, imgBackground, font);
								}
							}

						}
						if (leaderboard.getFillColor() == Color::Red) showLeaderboard(window, imgBackground, font);
						if (exitGame.getFillColor() == Color::Red) displayExitBox(font, window, icon);
					}

					break;
			}

		}

		window.clear();
		window.draw(imgBackground);
		window.draw(title);
		window.draw(imgSnake);
		window.draw(playGame);
		window.draw(leaderboard);
		window.draw(exitGame);
		window.draw(control);
		window.display();
	}

	return 0;
}
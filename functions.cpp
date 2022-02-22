#include "functions.h"
#include "leaderboard.h"

int key = 0;

void endGame(RenderWindow &window, Font font, Sprite imgBackground, int delay) {

	extern int score;
	std::string scoreStr = std::to_string(score);
	
	std::string apples = "Your snake ate ";
	apples.append(scoreStr);
	if (score == 1) apples.append(" apple!");
	else apples.append(" apples!");

	extern int points;
	std::string pointsStr = std::to_string(points);

	std::string pointsText = "You scored ";
	pointsText.append(pointsStr);
	pointsText.append(" points!");

	score = 0;

	Text end1;
	end1.setString(apples);
	end1.setFont(font);
	end1.setFillColor(Color::White);
	end1.setOutlineColor(Color(77, 45, 14));
	end1.setOutlineThickness(3);
	end1.setLetterSpacing(2);
	end1.setCharacterSize(64);
	end1.setPosition(window.getSize().x / 2.f - end1.getGlobalBounds().width / 2.f, 80);

	Text end2;
	end2.setString(pointsText);
	end2.setFont(font);
	end2.setFillColor(Color::White);
	end2.setOutlineColor(Color(77, 45, 14));
	end2.setOutlineThickness(3);
	end2.setLetterSpacing(2);
	end2.setCharacterSize(64);
	end2.setPosition(window.getSize().x / 2.f - end2.getGlobalBounds().width / 2.f, 280);

	Text end3;
	end3.setString("Do you want to be in leaderboard?");
	end3.setFont(font);
	end3.setFillColor(Color::White);
	end3.setOutlineColor(Color(77, 45, 14));
	end3.setOutlineThickness(3);
	end3.setLetterSpacing(2);
	end3.setCharacterSize(64);
	end3.setPosition(window.getSize().x / 2.f - end3.getGlobalBounds().width / 2.f, 480);

	Text yes;
	yes.setString("Yes - press Enter");
	yes.setFont(font);
	yes.setCharacterSize(24);
	yes.setFillColor(Color::Green);
	yes.setOutlineColor(Color::Black);
	yes.setOutlineThickness(2);
	yes.setLetterSpacing(1);
	yes.setPosition(window.getSize().x / 3.f - yes.getGlobalBounds().width / 2.f, 650);

	Text no;
	no.setString("No - press Esc");
	no.setFont(font);
	no.setCharacterSize(24);
	no.setPosition(10, 10);
	no.setFillColor(Color::Red);
	no.setOutlineColor(Color::Black);
	no.setOutlineThickness(2);
	no.setLetterSpacing(1);
	no.setPosition(2 * window.getSize().x / 3.f - no.getGlobalBounds().width / 2.f, 650);

	window.clear();
	window.draw(imgBackground);
	window.draw(end1);
	window.draw(end2);
	window.draw(end3);
	window.draw(yes);
	window.draw(no);
	window.display();

	while (window.isOpen())
	{	
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape) {
					key = 27; 
					return;
				}
				if (event.key.code == Keyboard::Enter) {
					key = 13; 
					return;
				}
			}
		}
	}
}

void displayExitBox(Font font, RenderWindow &window, Image icon)
{
	RenderWindow messageBox(VideoMode(648, 400), "Exit", Style::Titlebar | Style::Close);

	Texture headTex;
	headTex.loadFromFile("images/head.jpg");
	
	Sprite head;
	head.setTexture(headTex);
	head.setScale(0.3, 0.3);
	head.setPosition(messageBox.getSize().x - head.getGlobalBounds().width, -20);

	Text exitQuestion1;
	exitQuestion1.setString("Do you want to");
	exitQuestion1.setFont(font);
	exitQuestion1.setFillColor(Color::White);
	exitQuestion1.setOutlineColor(Color::Black);
	exitQuestion1.setOutlineThickness(3);
	exitQuestion1.setCharacterSize(36);
	exitQuestion1.setLetterSpacing(2);
	exitQuestion1.setPosition(messageBox.getSize().x / 3.f - head.getGlobalBounds().width / 2.f, messageBox.getSize().y / 5.f);

	Text exitQuestion2;
	exitQuestion2.setString("exit the game?");
	exitQuestion2.setFont(font);
	exitQuestion2.setFillColor(Color::White);
	exitQuestion2.setOutlineColor(Color::Black);
	exitQuestion2.setOutlineThickness(3);
	exitQuestion2.setCharacterSize(36);
	exitQuestion2.setLetterSpacing(2);
	exitQuestion2.setPosition(messageBox.getSize().x / 3.f - head.getGlobalBounds().width / 2.f, messageBox.getSize().y / 4.f + exitQuestion2.getGlobalBounds().height);

	Text yes;
	yes.setString("Yes - press Enter");
	yes.setFont(font);
	yes.setCharacterSize(24);
	yes.setFillColor(Color::Green);
	yes.setOutlineColor(Color::Black);
	yes.setOutlineThickness(2);
	yes.setLetterSpacing(1);
	yes.setPosition(messageBox.getPosition().x / 4.f - yes.getGlobalBounds().width / 2.f, 300);

	Text no;
	no.setString("No - press Esc");
	no.setFont(font);
	no.setCharacterSize(24);
	no.setPosition(10, 10);
	no.setFillColor(Color::Red);
	no.setOutlineColor(Color::Black);
	no.setOutlineThickness(2);
	no.setLetterSpacing(1);
	no.setPosition(messageBox.getPosition().x / 3.f + no.getGlobalBounds().width / 2.f, 300);

	messageBox.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	messageBox.clear(Color(69, 159, 160, 1));
	messageBox.draw(head);
	messageBox.draw(exitQuestion1);
	messageBox.draw(exitQuestion2);
	messageBox.draw(yes);
	messageBox.draw(no);
	messageBox.display();

	while (messageBox.isOpen()) {
		Event mEvent;
		while (messageBox.pollEvent(mEvent)) {
			switch (mEvent.type) {
			case Event::Closed:
				messageBox.close();
				break;
			case Event::KeyPressed:
				if (mEvent.key.code == Keyboard::Escape) messageBox.close();
				else if (mEvent.key.code == Keyboard::Enter) { messageBox.close(); window.close(); }
				break;
			}
		}
	}
}
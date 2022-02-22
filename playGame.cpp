#include "playGame.h"
#include "functions.h"

int length = 4;
int tileSize = 38;
int W = 32, H = 19;
int start = 0, gameOver = 0;
int dir = 4, score = 0;
int globalDelay;
int points = 0;
int gain = 0;
bool gameOn = false;

float timer = 0;

struct Snake {
	int x;
	int y;
} snake[608];

struct Fruit {
	int x;
	int y;
} fruit;

void startGame(RenderWindow &window, int delay) {
	
	globalDelay = delay;
	gameOn = true;
	srand(time(NULL));

	window.clear();

	Texture headTex;
	headTex.loadFromFile("images/head4.png");
	Sprite head;
	head.setTexture(headTex);

	Texture segmentTex;
	segmentTex.loadFromFile("images/segmenth.png");
	Sprite segment;
	segment.setTexture(segmentTex);

	Texture tailTex;
	tailTex.loadFromFile("images/tail4.png");
	Sprite tail;
	tail.setTexture(tailTex);
	
	Texture boundaryTex;
	boundaryTex.loadFromFile("images/brick.jpg");
	Sprite boundary;
	boundary.setTexture(boundaryTex);

	Texture grassTex;
	grassTex.loadFromFile("images/grass.jpg");
	Sprite grass;
	grass.setTexture(grassTex);

	Texture appleTex;
	appleTex.loadFromFile("images/apple.png");
	Sprite apple;
	apple.setTexture(appleTex);

	SoundBuffer appleBuf;
	appleBuf.loadFromFile("sounds/apple.wav");
	Sound appleSound;
	appleSound.setBuffer(appleBuf);

	Clock clock;

	placeFruit();

	while (window.isOpen()) {

		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		timer += time;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) && dir != 3) dir = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right) && dir != 4) dir = 2;
		if (Keyboard::isKeyPressed(Keyboard::Down) && dir != 1) dir = 3;
		if (Keyboard::isKeyPressed(Keyboard::Left) && dir != 2) dir = 4;

		window.clear();

		for (int i = 0; i <= window.getSize().x; i += boundary.getGlobalBounds().width) {
			boundary.setPosition(i, 0);
			window.draw(boundary);
			boundary.setPosition(i, window.getSize().y - boundary.getGlobalBounds().height);
			window.draw(boundary);
		}

		for (int i = boundary.getGlobalBounds().height; i <= window.getSize().y - boundary.getGlobalBounds().height; i += boundary.getGlobalBounds().height) {
			boundary.setPosition(0, i);
			window.draw(boundary);
			boundary.setPosition(window.getSize().x - boundary.getGlobalBounds().width, i);
			window.draw(boundary);
		}

		grass.setPosition(boundary.getGlobalBounds().width, boundary.getGlobalBounds().height);
		window.draw(grass);

		apple.setPosition(fruit.x, fruit.y);
		window.draw(apple);

		if (timer > delay) { timer = 0; checkApple(window, tail, segment); moveSnake(); }

		if (gain == 1) { appleSound.play(); gain = 0; }

		if (start == 0) firstDraw();

		for (int i = 0; i < length; i++) {

			if (i == 0) {

				if (snake[i].y < snake[i + 1].y) headTex.loadFromFile("images/head1.png");
				else if (snake[i].x > snake[i + 1].x) headTex.loadFromFile("images/head2.png");
				else if (snake[i].y > snake[i + 1].y) headTex.loadFromFile("images/head3.png");
				else if (snake[i].x < snake[i + 1].x) headTex.loadFromFile("images/head4.png");

				head.setTexture(headTex);
				head.setPosition(snake[i].x, snake[i].y);
				window.draw(head);
			}

			else if (i == length - 1) {
				if (snake[i].y > snake[i - 1].y) tailTex.loadFromFile("images/tail1.png");
				else if (snake[i].x < snake[i - 1].x) tailTex.loadFromFile("images/tail2.png");
				else if (snake[i].y < snake[i - 1].y) tailTex.loadFromFile("images/tail3.png");
				else if (snake[i].x > snake[i - 1].x) tailTex.loadFromFile("images/tail4.png");

				tail.setTexture(tailTex);
				tail.setPosition(snake[i].x, snake[i].y);
				window.draw(tail);
			}

			else {
				int psegX = snake[i - 1].x;
				int psegY = snake[i - 1].y;
				int nsegX = snake[i + 1].x;
				int nsegY = snake[i + 1].y;

				if (psegX < snake[i].x && nsegX > snake[i].x || psegX > snake[i].x && nsegX < snake[i].x) segmentTex.loadFromFile("images/segmenth.png");
				else if (psegY < snake[i].y && nsegY > snake[i].y || psegY > snake[i].y && nsegY < snake[i].y) segmentTex.loadFromFile("images/segmentv.png");
				else if (psegY > snake[i].y && nsegX > snake[i].x || psegX > snake[i].x && nsegY > snake[i].y) segmentTex.loadFromFile("images/bend12-43.png");
				else if (psegY < snake[i].y && nsegX < snake[i].x || psegX < snake[i].x && nsegY < snake[i].y) segmentTex.loadFromFile("images/bend21-34.png");
				else if (psegY > snake[i].y && nsegX < snake[i].x || psegX < snake[i].x && nsegY > snake[i].y) segmentTex.loadFromFile("images/bend23-14.png");
				else if (psegY < snake[i].y && nsegX > snake[i].x || psegX > snake[i].x && nsegY < snake[i].y) segmentTex.loadFromFile("images/bend32-41.png");

				segment.setTexture(segmentTex);
				segment.setPosition(snake[i].x, snake[i].y);
				window.draw(segment);
			}
		}

		window.display();

		checkCollision(window);

		if (gameOver == 1) {
			gameOverFun(window);
			return;
		}
	}
}

void gameOverFun(RenderWindow &window) {
	
	SoundBuffer gameOverBuf;
	gameOverBuf.loadFromFile("sounds/gameover.wav");
	Sound gameOverSound;
	gameOverSound.setBuffer(gameOverBuf);
	gameOverSound.play();

	Texture gameOverTex;
	gameOverTex.loadFromFile("images/gameover.png");
	Sprite gameOverSpr;
	gameOverSpr.setTexture(gameOverTex);
	gameOverSpr.setPosition(window.getSize().x / 2.f - gameOverSpr.getGlobalBounds().width / 2.f, window.getSize().y / 2.f - gameOverSpr.getGlobalBounds().height / 2.f);

	window.draw(gameOverSpr);
	window.display();
	sleep(seconds(3));
	
	points = score * 2000 / globalDelay;
	gameOver = 0;
	start = 0;
	length = 4;
}

void moveSnake() {

	for (int i = length - 1; i > 0; i--) {
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}

	if (dir == 1) snake[0].y -= tileSize;
	else if (dir == 2) snake[0].x += tileSize;
	else if (dir == 3) snake[0].y += tileSize;
	else if (dir == 4) snake[0].x -= tileSize;

	
	if (snake[0].x == snake[2].x && snake[0].y == snake[2].y) {
		//printf("overlap\n");

		for (int i = 0; i < length - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		
		if (dir == 1) { snake[length - 1].y -= tileSize; dir = 2;}
		else if (dir == 2) { snake[length - 1].x += tileSize; dir = 3; }
		else if (dir == 3) { snake[length - 1].y += tileSize; dir = 4; }
		else if (dir == 4) { snake[length - 1].x -= tileSize; dir = 1; }
	}
}

void checkApple(RenderWindow &window, Sprite tail, Sprite segment) {

	if (snake[0].x == fruit.x && snake[0].y == fruit.y) {

		gain = 1;
		score++;
		length++;
		placeFruit();
	}
}

void checkCollision(RenderWindow &window) {

	if (snake[0].x <= tileSize || snake[0].y <= tileSize || 
		snake[0].x >= window.getSize().x - tileSize || 
		snake[0].y >= window.getSize().y - tileSize) gameOver = 1;

	for (int i = 4; i < length; i++) {
		
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			gameOver = 1;
			break;
		}
	}
}

void placeFruit() {


	int x, y;
	do x = ((rand() % (W - 1)) + 2) * tileSize;
	while (checkOverlapX(x));

	do 	y = ((rand() % (H - 1)) + 2) * tileSize;
	while (checkOverlapY(y));
	
	fruit.x = x;
	fruit.y = y;
}

int checkOverlapX(int x) {

	for (int i = 0; i < length; i++) {
		if (x == snake[i].x) return 1;
	}
	return 0;
}

int checkOverlapY(int y) {

	for (int i = 0; i < length; i++) {
		if (y == snake[i].y) return 1;
	}
	return 0;
}

void firstDraw() {

	start = 1;

	snake[0].x = ((rand() % (W - 4)) + 2) * tileSize;
	snake[0].y = ((rand() % (H - 1)) + 2) * tileSize;

	for (int i = 1; i < length - 1; i++) {
		snake[i].x = snake[0].x + i * tileSize;
		snake[i].y = snake[0].y;
	}

	snake[length - 1].x = snake[0].x + (length - 1) * tileSize;
	snake[length - 1].y = snake[0].y;
}

void chooseLevel(RenderWindow &window, Font font, Sprite imgBackground) {

	Text chooseLevel;
	chooseLevel.setString("Choose your difficulty level:");
	chooseLevel.setFont(font);
	chooseLevel.setFillColor(Color::White);
	chooseLevel.setOutlineColor(Color(77, 45, 14));
	chooseLevel.setOutlineThickness(3);
	chooseLevel.setLetterSpacing(2);
	chooseLevel.setCharacterSize(64);
	chooseLevel.setPosition(window.getSize().x / 2.f - chooseLevel.getGlobalBounds().width / 2.f, 80);

	Text slug;
	slug.setString("Slug");
	slug.setFont(font);
	slug.setFillColor(Color::White);
	slug.setOutlineColor(Color(77, 45, 14));
	slug.setOutlineThickness(3);
	slug.setLetterSpacing(2);
	slug.setCharacterSize(48);
	slug.setPosition(window.getSize().x / 2.f - slug.getGlobalBounds().width / 2.f, 220);

	Text worm;
	worm.setString("Worm");
	worm.setFont(font);
	worm.setFillColor(Color::White);
	worm.setOutlineColor(Color(77, 45, 14));
	worm.setOutlineThickness(3);
	worm.setLetterSpacing(2);
	worm.setCharacterSize(48);
	worm.setPosition(window.getSize().x / 2.f - worm.getGlobalBounds().width / 2.f, 340);

	Text python;
	python.setString("Python");
	python.setFont(font);
	python.setFillColor(Color::White);
	python.setOutlineColor(Color(77, 45, 14));
	python.setOutlineThickness(3);
	python.setLetterSpacing(2);
	python.setCharacterSize(48);
	python.setPosition(window.getSize().x / 2.f - python.getGlobalBounds().width / 2.f, 460);

	Text blackMamba;
	blackMamba.setString("Black Mamba");
	blackMamba.setFont(font);
	blackMamba.setFillColor(Color::White);
	blackMamba.setOutlineColor(Color(77, 45, 14));
	blackMamba.setOutlineThickness(3);
	blackMamba.setLetterSpacing(2);
	blackMamba.setCharacterSize(48);
	blackMamba.setPosition(window.getSize().x / 2.f - blackMamba.getGlobalBounds().width / 2.f, 580);

	int pressCounter = -1;

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
				case Event::Closed:
					window.close();
					break;

				case Event::KeyPressed:
					if (event.key.code == Keyboard::Escape) {
						if (slug.getFillColor() == Color::Red || worm.getFillColor() == Color::Red || python.getFillColor() == Color::Red || blackMamba.getFillColor() == Color::Red) {
							slug.setFillColor(Color::White);
							worm.setFillColor(Color::White);
							python.setFillColor(Color::White);
							blackMamba.setFillColor(Color::White);
						}
						else return;
					}

					if (event.key.code == Keyboard::Down) {
						pressCounter += 1;

						switch (pressCounter % 4) {
							case 0:
								slug.setFillColor(Color::Red);
								worm.setFillColor(Color::White);
								python.setFillColor(Color::White);
								blackMamba.setFillColor(Color::White);
								break;
							case 1:
								slug.setFillColor(Color::White);
								worm.setFillColor(Color::Red);
								python.setFillColor(Color::White);
								blackMamba.setFillColor(Color::White);
								break;
							case 2:
								slug.setFillColor(Color::White);
								worm.setFillColor(Color::White);
								python.setFillColor(Color::Red);
								blackMamba.setFillColor(Color::White);
								break;
							case 3:
								slug.setFillColor(Color::White);
								worm.setFillColor(Color::White);
								python.setFillColor(Color::White);
								blackMamba.setFillColor(Color::Red);
								break;
						}
					}

					if (event.key.code == Keyboard::Up) {
						if (slug.getFillColor() == Color::Red) {
							slug.setFillColor(Color::White);
							worm.setFillColor(Color::White);
							python.setFillColor(Color::White);
							blackMamba.setFillColor(Color::Red);
						}
						else if (worm.getFillColor() == Color::Red) {
							slug.setFillColor(Color::Red);
							worm.setFillColor(Color::White);
							python.setFillColor(Color::White);
							blackMamba.setFillColor(Color::White);
						}
						else if (python.getFillColor() == Color::Red) {
							slug.setFillColor(Color::White);
							worm.setFillColor(Color::Red);
							python.setFillColor(Color::White);
							blackMamba.setFillColor(Color::White);
						}
						else if (blackMamba.getFillColor() == Color::Red) {
							slug.setFillColor(Color::White);
							worm.setFillColor(Color::White);
							python.setFillColor(Color::Red);
							blackMamba.setFillColor(Color::White);
						}
						else {
							slug.setFillColor(Color::Red);
							worm.setFillColor(Color::White);
							python.setFillColor(Color::White);
							blackMamba.setFillColor(Color::White);
						}
					}

					if (event.key.code == Keyboard::Enter) {
						if (slug.getFillColor() == Color::Red) { startGame(window, 400); return; }
						else if (worm.getFillColor() == Color::Red) { startGame(window, 300); return; }
						else if (python.getFillColor() == Color::Red) { startGame(window, 100); return; }
						else if (blackMamba.getFillColor() == Color::Red) { startGame(window, 75); return; }
					}
			}
		}

		window.clear();
		window.draw(imgBackground);
		window.draw(chooseLevel);
		window.draw(slug);
		window.draw(worm);
		window.draw(python);
		window.draw(blackMamba);
		window.display();
	}
}
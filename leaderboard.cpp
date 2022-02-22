#include "leaderboard.h"
#include "functions.h"
#include "playGame.h"

const int rankingSize = 7;
const int len = 25;
char rankingNames[rankingSize + 1][len];
int rankingScores[rankingSize + 1];
int minScore;
int maxScore;
int size = -1;
bool edited = false;

void showLeaderboard(RenderWindow &window, Sprite imgBackground, Font font) {

	int y = 180;
	if (edited) {
		saveSorted();
		edited = false;
	}

	Text leaderboard;
	leaderboard.setString("Leaderboard:");
	leaderboard.setFont(font);
	leaderboard.setFillColor(Color::White);
	leaderboard.setOutlineColor(Color(77, 45, 14));
	leaderboard.setOutlineThickness(3);
	leaderboard.setLetterSpacing(2);
	leaderboard.setCharacterSize(64);

	readRanking();

	if (size == -1) leaderboard.setString("Leaderboard is empty");
	leaderboard.setPosition(window.getSize().x / 2.f - leaderboard.getGlobalBounds().width / 2.f, 60);
	
	//for (int i = 0; i < size; i++) printf(" %s - %d\n", rankingNames[i], rankingScores[i]);

	window.clear();
	window.draw(imgBackground);
	window.draw(leaderboard);

	for (int i = 0; i < rankingSize; i++) {

		std::string scoreStr = std::to_string(rankingScores[i]);

		Text name;
		name.setString(rankingNames[i]);
		name.setFont(font);
		name.setFillColor(Color::White);
		name.setOutlineColor(Color(77, 45, 14));
		name.setOutlineThickness(3);
		name.setLetterSpacing(2);
		name.setCharacterSize(44);
		name.setPosition(window.getSize().x / 5.f, y);

		Text score;
		score.setString(scoreStr);
		score.setFont(font);
		score.setFillColor(Color::White);
		score.setOutlineColor(Color(77, 45, 14));
		score.setOutlineThickness(3);
		score.setLetterSpacing(2);
		score.setCharacterSize(44);
		score.setPosition(window.getSize().x - name.getPosition().x - score.getGlobalBounds().width, y);

		if (rankingNames[i] != NULL && rankingScores[i] != NULL) {
			window.draw(name);
			window.draw(score);
			y += 80;
		}
	}

	window.display();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();

			if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Escape || event.key.code == Keyboard::Enter)) return;
		}
	}
}

void saveScore(RenderWindow &window, Sprite imgBackground, Font font) {

	String input = "";

	Text inputText;
	inputText.setFont(font);
	inputText.setFillColor(Color::White);
	inputText.setOutlineColor(Color(77, 45, 14));
	inputText.setOutlineThickness(3);
	inputText.setLetterSpacing(2);
	inputText.setCharacterSize(60);

	Text enterName;
	enterName.setString("Enter your name:");
	enterName.setFont(font);
	enterName.setFillColor(Color::White);
	enterName.setOutlineColor(Color(77, 45, 14));
	enterName.setOutlineThickness(3);
	enterName.setLetterSpacing(2);
	enterName.setCharacterSize(64);
	enterName.setPosition(window.getSize().x / 2.f - enterName.getGlobalBounds().width / 2.f, 80);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();

			if (event.type == Event::TextEntered) {

				if (event.text.unicode == '\b') input.erase(input.getSize() - 1, 1);

				if (event.text.unicode < 128) {
					if (input.getSize() < len - 1) {
						input += event.text.unicode;
						inputText.setString(input);
						inputText.setPosition(window.getSize().x / 2.f - inputText.getGlobalBounds().width / 2.f, 300);
					}
				}
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
				
				saveToFile(input);
				readRanking();
				showLeaderboard(window, imgBackground, font);
				
				return;
			}
		}

		window.clear();
		window.draw(imgBackground);
		window.draw(enterName);
		window.draw(inputText);
		window.display();
	}
}

void saveToFile(String input) {

	fflush(stdin);
	edited = true;

	std::string name;
	name = input;
	name.append(";");
	const char *nameCh = name.c_str();

	extern int points;
	std::string pointsStr = std::to_string(points);
	const char *pointsCh = pointsStr.c_str();

	FILE * fp = fopen("leaderboard.txt", "a");
	fputs("\n", fp);
	fputs(nameCh, fp);
	fputs(pointsCh, fp);
	fclose(fp);
}

void readRanking() {

	FILE *fp = fopen("leaderboard.txt", "r");

	size = -1;
	char buff[len + 6];
	char *token;
	const char *delim = ";";

	while (fgets(buff, sizeof(buff), fp)) {
		
		//printf(" %s\n", buff);

		if (size >= 0) {
			
			strcpy(rankingNames[size], strtok(buff, delim));
			token = strtok(NULL, delim);
			if (token != NULL) rankingScores[size] = atoi(token);
		}
		size++;
	}

	fclose(fp);

	bubbleusz();
}

void bubbleusz() {
	
	bool swapped;
	char tempN[len];

	for (int i = 0; i < size - 1; i++) {
		swapped = false;
		for (int j = 0; j < size - i - 1; j++) {

			if (rankingScores[j] < rankingScores[j + 1]) {

				int tempS = rankingScores[j];
				rankingScores[j] = rankingScores[j + 1];
				rankingScores[j + 1] = tempS;
				
				strcpy(tempN, rankingNames[j]);
				strcpy(rankingNames[j], rankingNames[j + 1]);
				strcpy(rankingNames[j + 1], tempN);
				
				swapped = true;
			}
		}
		if (swapped == false) break;
	}

	minScore = rankingScores[rankingSize - 1];
	maxScore = rankingScores[0];
	
	//printf("\nminScore: %d\n", minScore);
	//printf("maxScore: %d\n", maxScore);
}

void saveSorted() {

	FILE *fp = fopen("leaderboard.txt", "w");

	int writeCounter;
	if (size >= rankingSize) writeCounter = rankingSize;
	else writeCounter = size;

	for (int i = 0; i < writeCounter; i++) {
		std::string scoreStr = std::to_string(rankingScores[i]);
		const char *score = scoreStr.c_str();

		fputs("\n", fp);
		fputs(rankingNames[i], fp);
		fputs(";", fp);
		fputs(score, fp);
	}

	fclose(fp);
}

void newBestScore(RenderWindow &window, Sprite imgBackground, Font font) {

	Text congrats;
	congrats.setString("Congratulations!");
	congrats.setFont(font);
	congrats.setFillColor(Color::White);
	congrats.setOutlineColor(Color(77, 45, 14));
	congrats.setOutlineThickness(3);
	congrats.setLetterSpacing(2);
	congrats.setCharacterSize(64);
	congrats.setPosition(window.getSize().x / 2.f - congrats.getGlobalBounds().width / 2.f, 80);

	Text best;
	best.setString("New best score!");
	best.setFont(font);
	best.setFillColor(Color::White);
	best.setOutlineColor(Color(77, 45, 14));
	best.setOutlineThickness(3);
	best.setLetterSpacing(2);
	best.setCharacterSize(64);
	best.setPosition(window.getSize().x / 2.f - best.getGlobalBounds().width / 2.f, 180);

	Texture fireworksTex;
	fireworksTex.loadFromFile("images/fireworks.png");
	Sprite fireworks;
	fireworks.setTexture(fireworksTex);
	fireworks.setPosition(window.getSize().x / 2.f - fireworks.getGlobalBounds().width / 2.f, 270);

	SoundBuffer victoryBuf;
	victoryBuf.loadFromFile("sounds/victory.wav");
	Sound victory;
	victory.setBuffer(victoryBuf);

	window.clear();
	window.draw(imgBackground);
	window.draw(congrats);
	window.draw(best);
	window.draw(fireworks);
	window.display();
	victory.play();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();

			if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Escape || event.key.code == Keyboard::Enter)) return;
		}

		sleep(seconds(5));
		return;
	}
}

void notEnough(RenderWindow &window, Sprite imgBackground, Font font) {

	Text info1;
	info1.setString("Your snake wasn't good enough");
	info1.setFont(font);
	info1.setFillColor(Color::White);
	info1.setOutlineColor(Color(77, 45, 14));
	info1.setOutlineThickness(3);
	info1.setLetterSpacing(2);
	info1.setCharacterSize(64);
	info1.setPosition(window.getSize().x / 2.f - info1.getGlobalBounds().width / 2.f, 100);

	Text info2;
	info2.setString("to be in leaderboard :(");
	info2.setFont(font);
	info2.setFillColor(Color::White);
	info2.setOutlineColor(Color(77, 45, 14));
	info2.setOutlineThickness(3);
	info2.setLetterSpacing(2);
	info2.setCharacterSize(64);
	info2.setPosition(window.getSize().x / 2.f - info2.getGlobalBounds().width / 2.f, 300);

	SoundBuffer failBuf;
	failBuf.loadFromFile("sounds/fail.wav");
	Sound fail;
	fail.setBuffer(failBuf);
	
	window.clear();
	window.draw(imgBackground);
	window.draw(info1);
	window.draw(info2);
	window.display();
	fail.play();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();

			if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Escape || event.key.code == Keyboard::Enter)) return;
		}

		sleep(seconds(4.5));
		return;
	}
}
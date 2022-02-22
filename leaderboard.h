#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

void showLeaderboard(RenderWindow &window, Sprite imgBackground, Font font);

void saveScore(RenderWindow &window, Sprite imgBackground, Font font);

void saveToFile(String input);

void readRanking();

void bubbleusz();

void saveSorted();

void newBestScore(RenderWindow &window, Sprite imgBackground, Font font);

void notEnough(RenderWindow &window, Sprite imgBackground, Font font);
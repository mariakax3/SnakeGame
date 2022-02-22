#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

void startGame(RenderWindow &window, int delay);

void gameOverFun(RenderWindow &window);

void moveSnake();

void checkApple(RenderWindow &window, Sprite tail, Sprite segment);

void checkCollision(RenderWindow &window);

void placeFruit();

int checkOverlapX(int x);

int checkOverlapY(int y);

void firstDraw();

void chooseLevel(RenderWindow &board, Font font, Sprite imgBackground);
#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstring>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

void endGame(RenderWindow &window, Font font, Sprite imgBackground, int delay);

void displayExitBox(Font font, RenderWindow &window, Image icon);
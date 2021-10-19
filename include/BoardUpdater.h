#pragma once
#include <king/Engine.h>
#include <king/Updater.h>
#include <random>
#include<vector>
#include "Board.h"

#define BOARD_SIZE 8
#define NO_MATCHES 3
#define MAX_MATCHES (2 * NO_MATCHES) - 1  // max numbers of matches following a matching swap

bool isKeyValid(int x);

class BoardUpdater : public King::Updater {
public:
	BoardUpdater();
	void Start();
	void handleMouseClick();
	void Update();
	void renderDiamonds();

private:
	King::Engine mEngine;
	Board mBoard;

	int firstClickCol;
	int firstClickRow;
	int secondClickCol;
	int secondClickRow;
	int firstClickValue;
	int secondClickValue;
};

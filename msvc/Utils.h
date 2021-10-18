#pragma once

#include <random>
#include<vector>

#define BOARD_SIZE 8
#define NO_MATCHES 3
#define MAX_MATCHES 5

struct matchItem
{
	int x;
	int y;
	int sequence;
	bool isX;
}; 

bool isValid(int x);

std::vector<std::vector<int>> generateInitialDiamonds();
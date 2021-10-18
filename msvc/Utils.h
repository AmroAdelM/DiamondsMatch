#pragma once

#include <random>
#include<vector>

#define BOARD_SIZE 8

struct matchItem
{
	int x;
	int y;
	int sequence;
	bool isX;
}; 

bool isValid(int x);

std::vector<std::vector<int>> generateInitialDiamonds();
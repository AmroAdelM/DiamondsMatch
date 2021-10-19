#pragma once

#include<vector>
#include "Utils.h"

void swapMatches(std::vector<std::vector<int>>&aDiamonds, std::vector<matchItem> aItems);
std::vector<matchItem> getMatchedDiamonds(std::vector<std::vector<int>>& aDiamonds);
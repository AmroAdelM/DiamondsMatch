#pragma once

#include<vector>
struct matchItem
{
	int x;
	int y;
	int sequence;
	bool isHorizontalMatch;
};

class Board
{
public:
	Board(int aBoard_size, int aMatch, int aMax);
	void generateInitialDiamonds();
	void swapMatches(const std::vector<matchItem>& aItems);
	void setDiamond(int x, int y, int value);
	int getDiamond(int x, int y);
	int getHorizontalMatchCount(int x, int y);
	int getVerticalMatchCount(int x, int y);
	std::vector<matchItem> getMatchedDiamonds();

private:
	std::vector<std::vector<int>> mDiamonds;
	int mBoardSize;
	int mNo_Matches;
	int mMax_Matches;
};
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
	void replaceMatches(const std::vector<matchItem>& aItems);
	void replaceHorizontal(const matchItem& aItems, const int& position);
	void replaceVertical(const matchItem& aItems, const int& position);
	void setDiamond(const int& x, const int& y, const int& value);
	int getDiamond(const int& x, const int& y);
	int getHorizontalMatchCount(const int& x, const int& y);
	int getVerticalMatchCount(const int& x, const int& y);
	std::vector<matchItem> getMatchedDiamonds();
	bool hasMatch(const int& cellX, const int& cellY);

private:
	std::vector<std::vector<int>> mDiamonds;
	int mBoardSize;
	int mNo_Matches;
	int mMax_Matches;
};
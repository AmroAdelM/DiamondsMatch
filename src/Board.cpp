#include "Board.h"
#include "BoardUpdater.h"

Board::Board(int aBoard_size, int aMatch, int aMax)
	: mBoardSize(aBoard_size), mNo_Matches(aMatch), mMax_Matches(aMax)
{
	mDiamonds = std::vector<std::vector<int>>(mBoardSize, std::vector<int>(mBoardSize, 0));
}

int Board::getDiamond(const int& x, const int& y)
{
	return mDiamonds[x][y];
}

void Board::setDiamond(const int& x, const int& y, const int& value)
{
	mDiamonds[x][y] = value;
}

void Board::generateInitialDiamonds()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> randomGenerator(1, 5); // distribution in range [1, 5] for colors only in King::Engine::TEXTURE 

	for (auto row = 0; row < BOARD_SIZE; row++)
	{
		for (auto col = 0; col < BOARD_SIZE; col++)
		{
			auto newDmnd = randomGenerator(rng);
			mDiamonds[row][col] = newDmnd;

			//check col matches before adding the new random diamond
			if (col > 1)
			{
				if (newDmnd == mDiamonds[row][col - 1] && newDmnd == mDiamonds[row][col - 2])
				{
					while (newDmnd == mDiamonds[row][col])
					{
						newDmnd = randomGenerator(rng);
					}
				}
			}

			//check row matches before adding the new random diamond
			if (row > 1)
			{
				if (newDmnd == mDiamonds[row - 1][col] && newDmnd == mDiamonds[row - 2][col])
				{
					while (newDmnd == mDiamonds[row][col])
					{
						newDmnd = randomGenerator(rng);
					}
				}
			}

			mDiamonds[row][col] = newDmnd;
		}
	}
};

void Board::replaceMatches(const std::vector<matchItem>& aItems)
{
	for (const auto& matchedItem : aItems)
	{
		for (int position = matchedItem.sequence; (position > 0) && isKeyValid(position + (matchedItem.isHorizontalMatch ? matchedItem.x : matchedItem.y)); position--)
		{
			if (matchedItem.isHorizontalMatch)
			{
				replaceHorizontal(matchedItem, position);
			}
			else
			{
				replaceVertical(matchedItem, position);
			}
		}
	}
}

void Board::replaceHorizontal(const matchItem& matchedItem, const int& position)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> randomGenerator(1, 5); //King::Engine::Texture
	auto newDmnd = randomGenerator(rng);

	auto iterator = matchedItem.y;
	while (iterator >= 0)
	{
		if (iterator > 0)
		{
			mDiamonds[iterator][matchedItem.x + position - 1] = mDiamonds[iterator - 1][matchedItem.x + position - 1];
			iterator--;
		}
		else
		{
			mDiamonds[iterator][matchedItem.x + position - 1] = newDmnd;
			if (newDmnd == mDiamonds[iterator+1][matchedItem.x + position - 1]
				&& newDmnd == mDiamonds[iterator+2][matchedItem.x + position - 1])
			{
				while (newDmnd == mDiamonds[iterator][matchedItem.x + position - 1])
				{
					newDmnd = randomGenerator(rng);
				}
			}
			mDiamonds[iterator][matchedItem.x + position - 1] = newDmnd;
			iterator--;
		}
	}
}

void Board::replaceVertical(const matchItem& matchedItem, const int& position)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> randomGenerator(1, 5); //King::Engine::Texture
	auto newDmnd = randomGenerator(rng);

	auto sequence = matchedItem.sequence;
	auto iterator = matchedItem.y + position - sequence - 1;
	if (iterator >= 0)
	{
		mDiamonds[matchedItem.y + position - 1][matchedItem.x] = mDiamonds[iterator][matchedItem.x];
		mDiamonds[iterator--][matchedItem.x] = newDmnd;
	}
	else
	{
		mDiamonds[matchedItem.y + position - 1][matchedItem.x] = newDmnd;
	}
}

std::vector<matchItem> Board::getMatchedDiamonds()
{
	std::vector<matchItem> matches;
	for (int y = 0; y < BOARD_SIZE; ++y)
	{
		for (int x = 0; x < BOARD_SIZE; ++x)
		{
			int colMatchCount = 1;
			int rowMatchCount = 1;

			// look horizontally - there is no need to look up the last two columns
			if (x < BOARD_SIZE)
			{
				colMatchCount = getHorizontalMatchCount(x, y);
			}

			// no need to look up the last two rows to look up the last two rows
			if (y < BOARD_SIZE)
			{
				rowMatchCount = getVerticalMatchCount(x, y);
			}

			// check if a sequence of matching colors has been found
			if (colMatchCount >= mNo_Matches || rowMatchCount >= mNo_Matches)
			{
				matchItem item;
				item.x = x;
				item.y = y;
				item.isHorizontalMatch = (colMatchCount >= mNo_Matches);
				item.sequence = item.isHorizontalMatch ? colMatchCount : rowMatchCount;
				matches.push_back(item);
			}
		}
	}
	return matches;
}

bool Board::hasMatch(const int& cellY, const int& cellX)
{
	int sourceColor = mDiamonds[cellY][cellX];

	// look right
	if (cellX < (BOARD_SIZE - 2))
	{
		if (sourceColor == mDiamonds[cellY][cellX + 1]
			&& sourceColor == mDiamonds[cellY][cellX + 2])
		{
			return true;
		}
	}

	// look left
	if (cellX > 1)
	{
		if (sourceColor == mDiamonds[cellY][cellX - 1]
			&& sourceColor == mDiamonds[cellY][cellX - 2])
		{
			return true;
		}
	}

	// look left and right 1 field
	if (cellX > 0 && cellX < (BOARD_SIZE - 1))
	{
		if (sourceColor == mDiamonds[cellY][cellX - 1]
			&& sourceColor == mDiamonds[cellY][cellX + 1])
		{
			return true;
		}
	}

	// look down
	if (cellY < (BOARD_SIZE - 2))
	{
		if (sourceColor == mDiamonds[cellY + 1][cellX]
			&& sourceColor == mDiamonds[cellY + 2][cellX])
		{
			return true;
		}
	}

	// look up
	if (cellY > 1)
	{
		if (sourceColor == mDiamonds[cellY - 1][cellX]
			&& sourceColor == mDiamonds[cellY - 2][cellX])
		{
			return true;
		}
	}

	// look up and down 1 field
	if (cellY > 0 && cellY < (BOARD_SIZE - 1))
	{
		if (sourceColor == mDiamonds[cellY - 1][cellX]
			&& sourceColor == mDiamonds[cellY + 1][cellX])
		{
			return true;
		}
	}

	return false;
}

int Board::getHorizontalMatchCount(const int& x, const int& y)
{
	int currentColor = mDiamonds[y][x];
	int matchingColor = currentColor;
	int colMatchCount = 1;

	while (colMatchCount > 0 && colMatchCount < mMax_Matches)
	{
		int xPosition = x + colMatchCount;
		if (isKeyValid(xPosition))
		{
			matchingColor = mDiamonds[y][xPosition];
		}
		else
		{
			break;
		}

		if (currentColor == matchingColor)
		{
			++colMatchCount;
			//increase match Count
		}
		else
		{
			break;
			// break sequence if colors don't match anymore
		}
	}

	return colMatchCount;
}

int Board::getVerticalMatchCount(const int& x, const int& y)
{
	int currentColor = mDiamonds[y][x];
	int matchingColor = currentColor;
	int rowMatchCount = 1;

	while (rowMatchCount > 0 && rowMatchCount < mMax_Matches)
	{
		int yPosition = y + rowMatchCount;
		if (isKeyValid(yPosition))
		{
			matchingColor = mDiamonds[yPosition][x];
		}
		else
		{
			break;
		}

		if (currentColor == matchingColor)
		{
			++rowMatchCount;
			//increase match Count if it's the same

		}
		else
		{
			break;
			// break sequence if colors don't match anymore
		}
	}
	return rowMatchCount;
}
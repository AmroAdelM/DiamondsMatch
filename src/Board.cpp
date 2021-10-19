#include "Board.h"
#include "BoardUpdater.h"

Board::Board(int aBoard_size, int aMatch, int aMax)
	: mBoardSize(aBoard_size), mNo_Matches(aMatch), mMax_Matches(aMax), mDiamonds(mBoardSize, std::vector<int>(mBoardSize)){}

int Board::getDiamond(int x, int y)
{
	return mDiamonds[x][y];
}

void Board::setDiamond(int x, int y, int value)
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

void Board::swapMatches(const std::vector<matchItem>& aItems)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> randomGenerator(1, 5); //King::Engine::Texture
	for (const auto& matchedItem : aItems)
	{
		for (int position = matchedItem.sequence; (position > 0) && isKeyValid(position + (matchedItem.isHorizontalMatch ? matchedItem.x : matchedItem.y)); position--)
		{
			auto sequence = matchedItem.sequence;
			auto newDmnd = randomGenerator(rng);
			if (matchedItem.isHorizontalMatch)
			{
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
						iterator--;
					}
				}
			}
			else
			{
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
		}
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
			if (x <= (BOARD_SIZE - NO_MATCHES))
			{
				colMatchCount = getHorizontalMatchCount(x, y);
			}

			// no need to look up the last two rows to look up the last two rows
			if (y <= (BOARD_SIZE - NO_MATCHES - 1))
			{
				rowMatchCount = getVerticalMatchCount(x, y);
			}

			// check if a sequence of matching colors has been found
			if (colMatchCount >= NO_MATCHES || rowMatchCount >= NO_MATCHES)
			{
				matchItem item;
				item.x = x;
				item.y = y;
				item.isHorizontalMatch = (colMatchCount >= NO_MATCHES);

				item.sequence = item.isHorizontalMatch ? colMatchCount : rowMatchCount;
				matches.push_back(item);
			}
		}
	}
	return matches;
}

int Board::getHorizontalMatchCount(int x, int y)
{
	int currentColor = mDiamonds[y][x];
	int matchingColor = currentColor;
	int colMatchCount = 1;

	while (colMatchCount > 0 && colMatchCount < MAX_MATCHES)
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

int Board::getVerticalMatchCount(int x, int y)
{
	int currentColor = mDiamonds[y][x];
	int matchingColor = currentColor;
	int rowMatchCount = 1;

	while (rowMatchCount > 0 && rowMatchCount < MAX_MATCHES)
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
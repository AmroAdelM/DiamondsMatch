#include "Board.h"
#include "Utils.h"

void swapMatches(std::vector<std::vector<int>>& aDiamonds, std::vector<matchItem> aItems)
{
	//std::vector<std::vector<int>> mDiamonds;

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> randomGenerator(1, 5); //King::Engine::Texture
	for (const auto& matchedItem : aItems)
	{
		for (int position = matchedItem.sequence; (position > 0) && isValid(position + (matchedItem.isX ? matchedItem.x : matchedItem.y)); position--)
		{
			auto sequence = matchedItem.sequence;
			auto newDmnd = randomGenerator(rng);
			if (matchedItem.isX)
			{
				auto iterator = matchedItem.y;
				while (iterator >= 0)
				{
					if (iterator > 0)
					{
						aDiamonds[iterator][matchedItem.x + position - 1] = aDiamonds[iterator - 1][matchedItem.x + position - 1];
						iterator--;
					}
					else
					{
						aDiamonds[iterator][matchedItem.x + position - 1] = newDmnd;
						iterator--;
					}
				}
			}
			else
			{
				auto iterator = matchedItem.y + position - sequence - 1;
				if (iterator >= 0)
				{
					aDiamonds[matchedItem.y + position - 1][matchedItem.x] = aDiamonds[iterator][matchedItem.x];
					aDiamonds[iterator--][matchedItem.x] = newDmnd;
				}
				else
				{
					aDiamonds[matchedItem.y + position - 1][matchedItem.x] = newDmnd;
				}
			}
		}
	}
}

std::vector<matchItem> getMatchedDiamonds(std::vector<std::vector<int>>& aDiamonds)
{
	std::vector<matchItem> matches;
	for (int y = 0; y < BOARD_SIZE; ++y)
	{
		for (int x = 0; x < BOARD_SIZE; ++x)
		{
			int currentColor = aDiamonds[y][x];
			int colMatchCount = 1;
			int rowMatchCount = 1;

			// look horizontally - there is no need to look up the last two columns
			if (x < 6)
			{
				int matchingColor = currentColor;
				while (colMatchCount > 0 && colMatchCount < MAX_MATCHES)
				{
					int searchPosition = x + colMatchCount;
					// get color of search position
					if (searchPosition < BOARD_SIZE)
					{
						matchingColor = aDiamonds[y][searchPosition];
					}

					// stop looking if the colors don't match
					if (currentColor != matchingColor)
					{
						break;
					}
					else
					{
						++colMatchCount;
					}
				}
			}

			// look vertically - there is no need to look up the last two rows
			if (y < 6)
			{
				int matchingColor = currentColor;

				while (rowMatchCount > 0 && rowMatchCount < MAX_MATCHES)
				{
					int searchPosition = y + rowMatchCount;
					// get color of search position
					if (searchPosition < BOARD_SIZE)
					{
						matchingColor = aDiamonds[searchPosition][x];
					}
					else
					{
						break;
					}
					// stop looking if the colors don't match
					if (currentColor != matchingColor)
					{
						break;
					}
					else
					{
						++rowMatchCount;
					}
				}
			}

			// check if a sequence of at least 3 horizontal matching color has been found
			if (colMatchCount >= NO_MATCHES)
			{
				matchItem item;
				item.x = x;
				item.y = y;
				item.sequence = colMatchCount;
				item.isX = true;
				matches.push_back(item);
			}
			// check if a sequence of at least 3 vertical matching color has been found
			if (rowMatchCount >= NO_MATCHES)
			{
				matchItem item;
				item.x = x;
				item.y = y;
				item.sequence = rowMatchCount;
				item.isX = false;
				matches.push_back(item);
			}
		}
	}
	return matches;
}


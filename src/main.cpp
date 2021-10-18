#define GLM_FORCE_RADIANS 

#include <king/Engine.h>
#include <king/Updater.h>
#include <random>
#include <iostream>
#include "../msvc/Utils.h"

//**********************************************************************
struct matchItem
{
	int x;
	int y;
	int sequence;
	bool isX;
};

class ExampleGame : public King::Updater {
public:
	ExampleGame()
		: mEngine("./assets")
		, mRotation(0.0f)
		, firstClick(0)
		, secondClick(0)
		, firstCol(-1)
		, firstRow(-1)
		, secondCol(-1)
		, secondRow(-1)
		, mDiamonds(BOARD_SIZE, std::vector<int>(BOARD_SIZE)) {
	}
	void generateInitialDiamonds()
	{
		std::vector<std::vector<int>> result;
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 5); // distribution in range [1, 5]

		for (auto row = 0; row < BOARD_SIZE; row++)
		{
			for (auto col = 0; col < BOARD_SIZE; col++)
			{
				auto newDmnd = dist6(rng);
				mDiamonds[row][col] = newDmnd;
				if (col > 1)
				{
					if (newDmnd == mDiamonds[row][col - 1] && newDmnd == mDiamonds[row][col - 2])
					{
						while (newDmnd == mDiamonds[row][col])
						{
							newDmnd = dist6(rng);
						}
						mDiamonds[row][col] = newDmnd;
					}
				}

				if (row > 1)
				{
					if (newDmnd == mDiamonds[row - 1][col] && newDmnd == mDiamonds[row - 2][col])
					{
						while (newDmnd == mDiamonds[row][col])
						{
							newDmnd = dist6(rng);
						}
						mDiamonds[row][col] = newDmnd;
					}
				}
			}
		}
	}

	void Start() {
		generateInitialDiamonds();
		mEngine.Start(*this);
	}

	void swapMatches(std::vector<matchItem> items)
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 5);
		for (const auto& matchedItem : items)
		{
			for (int position = matchedItem.sequence; (position > 0) && isValid(position + (matchedItem.isX ? matchedItem.x : matchedItem.y)); position--)
			{
				auto sequence = matchedItem.sequence;
				auto newDmnd = dist6(rng);
				if (matchedItem.isX)
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

	std::vector<matchItem> getMatchedDiamonds()
	{
		std::vector<matchItem> matches;
		// traverse the board rows to find horizontal color sequences
		for (int y = 0; y < BOARD_SIZE; ++y)
		{
			for (int x = 0; x < BOARD_SIZE; ++x)
			{
				//int position = y * m_Columns + x;
				int color = mDiamonds[y][x];
				// look in this row for a sequence
				int sequenceCountX = 1;
				int sequenceCountY = 1;

				// look horizontally - there is no need to look up the last two columns
				if (x < 6)
				{
					int matchingColor = color;
					while (sequenceCountX > 0 && sequenceCountX < 5)
					{
						int searchPosition = x + sequenceCountX;
						// get color of search position
						if (searchPosition < BOARD_SIZE)
						{
							matchingColor = mDiamonds[y][searchPosition];
						}

						// stop looking if the colors don't match
						if (matchingColor != color)
						{
							break;
						}
						else
						{
							++sequenceCountX;
						}
					}
				}

				// look vertically - there is no need to look up the last two rows
				if (y < 6)
				{
					int matchingColor = color;

					while (sequenceCountY > 0 && sequenceCountY < 5)
					{
						int searchPosition = y + sequenceCountY;
						// get color of search position
						if (searchPosition < BOARD_SIZE)
						{
							matchingColor = mDiamonds[searchPosition][x];
						}
						else
						{
							break;
						}
						// stop looking if the colors don't match
						if (matchingColor != color)
						{
							break;
						}
						else
						{
							++sequenceCountY;
						}
					}
				}

				// check if a sequence of at least 3 horizontal matching color has been found
				if (sequenceCountX >= 3)
				{
					matchItem item;
					item.x = x;
					item.y = y;
					item.sequence = sequenceCountX;
					item.isX = true;
					matches.push_back(item);
				}
				// check if a sequence of at least 3 vertical matching color has been found
				if (sequenceCountY >= 3)
				{
					matchItem item;
					item.x = x;
					item.y = y;
					item.sequence = sequenceCountY;
					item.isX = false;
					matches.push_back(item);
				}
			}
		}
		return matches;
	}

	void Update() {
		mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0, 0);

		//mRotation += mEngine.GetLastFrameSeconds();

		if (mEngine.GetMouseButtonDown())
		{
			float clickX = mEngine.GetMouseX();
			float clickY = mEngine.GetMouseY();

			int row = (clickX - 340.0) / 40;
			int col = (clickY - 120.0) / 40;

			if (isValid(col) && isValid(row))
			{
				if (firstClick == 0 && firstCol == -1 && firstRow == -1 && (row != secondRow || col != secondCol))
				{
					firstCol = col;
					firstRow = row;

					firstClick = mDiamonds[firstCol][firstRow];
					secondClick = 0;
					secondCol = -1;
					secondRow = -1;
				}
				else if (secondClick == 0 && secondCol == -1 && secondRow == -1 && (row != firstRow || col != firstCol))
				{
					secondCol = col;
					secondRow = row;
					if ((abs(secondCol - firstCol) + abs(secondRow - firstRow)) == 1)
					{
						secondClick = mDiamonds[secondCol][secondRow];
						mDiamonds[secondCol][secondRow] = firstClick;
						mDiamonds[firstCol][firstRow] = secondClick;
						swapMatches(getMatchedDiamonds());
					}
					firstClick = 0;
					firstRow = -1;
					firstCol = -1;
				}
			}
		}

		for (auto col = 0; col < BOARD_SIZE; col++)
		{
			for (auto row = 0; row < BOARD_SIZE; row++)
			{
				auto diamond = mDiamonds[col][row];
				if (diamond > 0 && diamond < 7)
				{
					mEngine.Render((King::Engine::Texture)diamond, 340 + (40.0f * row), 120 + (40.0f * col));
				}
			}
		}

		//mEngine.Render(King::Engine::TEXTURE_RED, 650.0f, 450.0f, mRotation);
		//mEngine.Render(King::Engine::TEXTURE_BLUE, 650.0f, 450.0f, mRotation);

		//mEngine.Write("Green", 650.0f, 140.0f);
		//mEngine.Write("Red", 100.0f, 490.0f);
		//mEngine.Write("Blue", 650.0f, 490.0f);

		//const char text[] = "This rotates at 5/PI Hz";
		//mEngine.Write(text, mEngine.GetWidth() / 2.0f, mEngine.GetHeight() / 2.0f, mRotation * 2.5f);

		//mEngine.Render(King::Engine::TEXTURE_YELLOW, mYellowDiamondX, mYellowDiamondY);
		//mEngine.Write("Click to", mYellowDiamondX, mYellowDiamondY + 40.0f);
		//mEngine.Write("move me!", mYellowDiamondX, mYellowDiamondY + 70.0f);

	}

private:
	std::vector<std::vector<int>> mDiamonds;

	King::Engine mEngine;
	float mRotation;

	int firstCol;
	int firstRow;
	int secondCol;
	int secondRow;
	int firstClick;
	int secondClick;
};

//**********************************************************************

int main(int argc, char* argv[]) {
	ExampleGame game;
	game.Start();

	return 0;
}
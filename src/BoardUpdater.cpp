#include "BoardUpdater.h"

bool isKeyValid(int x)
{
	return (x >= 0 && x < BOARD_SIZE);
}

BoardUpdater::BoardUpdater()
	: mEngine("./assets")
	, mBoard(BOARD_SIZE, NO_MATCHES, MAX_MATCHES)
	, firstClickValue(0)
	, secondClickValue(0)
	, firstClickCol(-1)
	, firstClickRow(-1)
	, secondClickCol(-1)
	, secondClickRow(-1) {}

void BoardUpdater::Update() {
	mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0, 0);

	if (mEngine.GetMouseButtonDown())
	{
		handleMouseClick();
	}

	renderDiamonds();
}

void BoardUpdater::handleMouseClick()
{
	float clickX = mEngine.GetMouseX();
	float clickY = mEngine.GetMouseY();

	int row = (int)(clickX - 340.0) / 40;
	int col = (int)(clickY - 120.0) / 40;

	if (isKeyValid(col) && isKeyValid(row))
	{
		if (firstClickValue == 0 && firstClickCol == -1 && firstClickRow == -1 && (row != secondClickRow || col != secondClickCol))
		{
			firstClickCol = col;
			firstClickRow = row;

			firstClickValue = mBoard.getDiamond(firstClickCol, firstClickRow);
			secondClickValue = 0;
			secondClickCol = -1;
			secondClickRow = -1;
		}
		else if (secondClickValue == 0 && secondClickCol == -1 && secondClickRow == -1 && (row != firstClickRow || col != firstClickCol))
		{
			secondClickCol = col;
			secondClickRow = row;
			if ((abs(secondClickCol - firstClickCol) + abs(secondClickRow - firstClickRow)) == 1)
			{
				secondClickValue = mBoard.getDiamond(secondClickCol, secondClickRow);

				mBoard.setDiamond(secondClickCol, secondClickRow, firstClickValue);
				mBoard.setDiamond(firstClickCol, firstClickRow, secondClickValue);

				// if no matches were caused by this swap revert it
				if (!mBoard.hasMatch(secondClickCol, secondClickRow)
					&& !mBoard.hasMatch(firstClickCol, firstClickRow))
				{
					mBoard.setDiamond(secondClickCol, secondClickRow, secondClickValue);
					mBoard.setDiamond(firstClickCol, firstClickRow, firstClickValue);
				}

				//check for swaps and replace them
				mBoard.replaceMatches(mBoard.getMatchedDiamonds());
			}
			firstClickValue = 0;
			firstClickRow = -1;
			firstClickCol = -1;
		}
	}
}

void BoardUpdater::Start() {
	mBoard.generateInitialDiamonds();
	mEngine.Start(*this);
}

void BoardUpdater::renderDiamonds()
{
	for (auto col = 0; col < BOARD_SIZE; col++)
	{
		for (auto row = 0; row < BOARD_SIZE; row++)
		{
			auto diamond = mBoard.getDiamond(col, row);
			if (diamond >= 1 && diamond <= 5) // in range [1, 5] for colors only in King::Engine::TEXTURE 
			{
				mEngine.Render((King::Engine::Texture)diamond, 340 + (40.0f * row), 120 + (40.0f * col));
			}
		}
	}
}

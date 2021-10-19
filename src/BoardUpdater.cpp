#include "BoardUpdater.h"

bool isKeyValid(int x)
{
	return (x >= 0 && x < BOARD_SIZE);
}

BoardUpdater::BoardUpdater()
	: mEngine("./assets")
	, mBoard(BOARD_SIZE, NO_MATCHES, MAX_MATCHES)
	, firstClick(0)
	, secondClick(0)
	, firstCol(-1)
	, firstRow(-1)
	, secondCol(-1)
	, secondRow(-1){}

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
		if (firstClick == 0 && firstCol == -1 && firstRow == -1 && (row != secondRow || col != secondCol))
		{
			firstCol = col;
			firstRow = row;

			firstClick = mBoard.getDiamond(firstCol, firstRow);
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
				secondClick = mBoard.getDiamond(secondCol, secondRow);
				mBoard.setDiamond(secondCol, secondRow, firstClick);
				mBoard.setDiamond(firstCol, firstRow, secondClick);
				mBoard.swapMatches(mBoard.getMatchedDiamonds());
			}
			firstClick = 0;
			firstRow = -1;
			firstCol = -1;
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

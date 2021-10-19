#define GLM_FORCE_RADIANS 

#include <king/Engine.h>
#include <king/Updater.h>
#include <iostream>
#include "../include/Utils.h"
#include"../include/Board.h"

//**********************************************************************

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
		, secondRow(-1) {
	}

	void Start() {
		mDiamonds = generateInitialDiamonds();
		mEngine.Start(*this);
	}

	void Update() {
		mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0, 0);

		//mRotation += mEngine.GetLastFrameSeconds();

		if (mEngine.GetMouseButtonDown())
		{
			float clickX = mEngine.GetMouseX();
			float clickY = mEngine.GetMouseY();

			int row = (int) (clickX - 340.0) / 40;
			int col = (int) (clickY - 120.0) / 40;

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
						swapMatches(mDiamonds, getMatchedDiamonds(mDiamonds));
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
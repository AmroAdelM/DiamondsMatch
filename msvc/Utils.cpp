#include "Utils.h"

bool isValid(int x)
{
	return (x >= 0 && x < BOARD_SIZE);
}

std::vector<std::vector<int>> generateInitialDiamonds()
{
	std::vector<std::vector<int>> mDiamonds(BOARD_SIZE, std::vector<int>(BOARD_SIZE));

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> randomGenerator(1, 5); // distribution in range [1, 5]

	for (auto row = 0; row < BOARD_SIZE; row++)
	{
		for (auto col = 0; col < BOARD_SIZE; col++)
		{
			auto newDmnd = randomGenerator(rng);
			mDiamonds[row][col] = newDmnd;

			//check column matches before adding the new random diamond
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
	return mDiamonds;
};
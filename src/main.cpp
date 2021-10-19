#define GLM_FORCE_RADIANS 

#include <iostream>
#include "../include/BoardUpdater.h"
#include"../include/Board.h"
#include "../include/BoardTest.h"

//**********************************************************************

int main(int argc, char* argv[]) {
	BoardUpdater game;
	game.Start();

	//::testing::InitGoogleTest(&argc, argv);
	//RUN_ALL_TESTS();

	return 0;
}
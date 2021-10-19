#include "gtest/gtest.h"
#include "BoardUpdater.h"


TEST(TestBoard, TestPopulatingDiamondsWithinRanges) {
	auto testBoard = new Board(BOARD_SIZE, NO_MATCHES, MAX_MATCHES);
	testBoard->generateInitialDiamonds();

	EXPECT_GE(testBoard->getDiamond(0,0), 1);
	EXPECT_LE(testBoard->getDiamond(0, 0), 5);
}

TEST(TestMatches, TestHorizontalMataches) {
	auto testBoard = new Board(BOARD_SIZE, NO_MATCHES, MAX_MATCHES);

	for(auto x = 0; x < BOARD_SIZE ; )

	EXPECT_GE(testBoard->getDiamond(0, 0), 1);
	EXPECT_LE(testBoard->getDiamond(0, 0), 5);
}
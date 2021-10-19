#include "gtest/gtest.h"
#include "BoardUpdater.h"


TEST(TestBoard, TestPopulatingDiamondsWithinRanges) {
	auto testBoard = new Board(BOARD_SIZE, NO_MATCHES, MAX_MATCHES);
	testBoard->generateInitialDiamonds();

	EXPECT_GE(testBoard->getDiamond(0, 0), 1);
	EXPECT_LE(testBoard->getDiamond(0, 0), 5);
}

TEST(TestMatches, TestHorizontalMataches) {
	auto testBoard = new Board(BOARD_SIZE, NO_MATCHES, MAX_MATCHES);

	testBoard->setDiamond(0, 0, 3);
	testBoard->setDiamond(0, 1, 3);
	testBoard->setDiamond(0, 2, 3);

	EXPECT_GE(testBoard->hasMatch(0, 0), true);
	EXPECT_LE(testBoard->hasMatch(0, 1), true);
}

TEST(TestMatches, TestVerticalMataches) {
	auto testBoard = new Board(BOARD_SIZE, NO_MATCHES, MAX_MATCHES);

	testBoard->setDiamond(0, 0, 3);
	testBoard->setDiamond(1, 0, 3);
	testBoard->setDiamond(2, 0, 3);

	EXPECT_GE(testBoard->hasMatch(0, 0), true);
	EXPECT_LE(testBoard->hasMatch(1, 0), true);
}

TEST(TestMatches, TestHoriz3MatchesCount) {
	auto testBoard = new Board(BOARD_SIZE, NO_MATCHES, MAX_MATCHES);

	testBoard->setDiamond(0, 0, 3);
	testBoard->setDiamond(0, 1, 3);
	testBoard->setDiamond(0, 2, 3);

	EXPECT_EQ(testBoard->getHorizontalMatchCount(0, 0), 3);
}

TEST(TestMatches, TestHoriz4MatchesCount) {
	auto testBoard = new Board(BOARD_SIZE, NO_MATCHES, MAX_MATCHES);

	testBoard->setDiamond(0, 0, 3);
	testBoard->setDiamond(0, 1, 3);
	testBoard->setDiamond(0, 2, 3);
	testBoard->setDiamond(0, 3, 3);

	EXPECT_EQ(testBoard->getHorizontalMatchCount(0, 0), 4);
}

TEST(TestMatches, TestVertical3Count) {
	auto testBoard = new Board(BOARD_SIZE, NO_MATCHES, MAX_MATCHES);

	testBoard->setDiamond(0, 0, 3);
	testBoard->setDiamond(1, 0, 3);
	testBoard->setDiamond(2, 0, 3);

	EXPECT_EQ(testBoard->getVerticalMatchCount(0, 0), 3);
}
TEST(TestMatches, TestVertical4Count) {
	auto testBoard = new Board(BOARD_SIZE, NO_MATCHES, MAX_MATCHES);

	testBoard->setDiamond(0, 0, 3);
	testBoard->setDiamond(1, 0, 3);
	testBoard->setDiamond(2, 0, 3);
	testBoard->setDiamond(3, 0, 3);

	EXPECT_EQ(testBoard->getVerticalMatchCount(0, 0), 4);
}

TEST(TestReplaced, TestReplacedFirstThreeHoriz) {
	auto testBoard = new Board(BOARD_SIZE, NO_MATCHES, MAX_MATCHES);
	testBoard->generateInitialDiamonds();

	testBoard->setDiamond(0, 0, 2);
	testBoard->setDiamond(0, 1, 4);
	testBoard->setDiamond(0, 2, 5);

	testBoard->setDiamond(1, 0, 3);
	testBoard->setDiamond(1, 1, 3);
	testBoard->setDiamond(1, 2, 3);

	testBoard->replaceMatches(testBoard->getMatchedDiamonds());

	EXPECT_EQ(testBoard->getDiamond(1, 0), 2);
	EXPECT_EQ(testBoard->getDiamond(1, 1), 4);
	EXPECT_EQ(testBoard->getDiamond(1, 2), 5);
}

TEST(TestReplaced, TestReplacedFirstThreeVert) {
	auto testBoard = new Board(BOARD_SIZE, NO_MATCHES, MAX_MATCHES);
	testBoard->generateInitialDiamonds();

	testBoard->setDiamond(0, 1, 2);
	testBoard->setDiamond(1, 1, 4);
	testBoard->setDiamond(2, 1, 5);

	testBoard->setDiamond(3, 1, 3);
	testBoard->setDiamond(4, 1, 3);
	testBoard->setDiamond(5, 1, 3);

	testBoard->replaceMatches(testBoard->getMatchedDiamonds());

	EXPECT_EQ(testBoard->getDiamond(3, 1), 2);
	EXPECT_EQ(testBoard->getDiamond(4, 1), 4);
	EXPECT_EQ(testBoard->getDiamond(5, 1), 5);
}
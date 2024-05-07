/**
 * @file: TestGameManager.cpp
 * @author: Justin P
 * @date: 2024-04-04
 */

#include "GameManager.h"
#include "gtest/gtest.h"

TEST(TestGameManager, testGameManager) {
  GameManager gm;

  // Testing GameManager::getDirection()
  EXPECT_EQ(gm.getDirection(0), "up");
  EXPECT_EQ(gm.getDirection(1), "down");
  EXPECT_EQ(gm.getDirection(2), "left");
  EXPECT_EQ(gm.getDirection(3), "right");
  EXPECT_EQ(gm.getDirection(100), "");
  EXPECT_EQ(gm.getLocations().size(), 0);
}

TEST(GameManagerTest, DisplayHelp) {
  GameManager gameManager;

  // Redirect std::cout to a stringstream to capture the output
  std::stringstream buffer;
  std::streambuf* prevCoutBuf = std::cout.rdbuf(buffer.rdbuf());

  // Call the method to test
  gameManager.displayHelp();

  // Restore the original buffer so that cout works normally after the test
  std::cout.rdbuf(prevCoutBuf);

  // Convert the buffer contents to a string
  std::string output = buffer.str();

  // Assert that the output contains expected help text
  ASSERT_NE(output.find("=== HELP ==="), std::string::npos);
  ASSERT_NE(output.find("Available commands:"), std::string::npos);
  ASSERT_NE(output.find("- help: Display this help message"),
            std::string::npos);
  ASSERT_NE(output.find("- quit: Quit the game"), std::string::npos);
}

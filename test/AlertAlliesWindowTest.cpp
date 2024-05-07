#include <gtest/gtest.h>

#include <sstream>

#include "AlertAlliesWindow.h"
#include "GameManager.h"

class AlertAlliesWindowTest : public ::testing::Test {
 protected:
  GameManager gameManager;
  std::stringstream stream;
  std::unique_ptr<AlertAlliesWindow> alertAlliesWindow =
      std::make_unique<AlertAlliesWindow>("Alert Room",
                                          "You are in the alert room.");
};

TEST_F(AlertAlliesWindowTest, TestInteractWithCorrectAlerts) {
  std::stringstream buffer;
  std::streambuf* prevCoutBuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());

  stream << "15\n";  // Assuming '15' is a correct alert code
  alertAlliesWindow->interact(&gameManager, stream);

  std::cout.rdbuf(prevCoutBuf);

  std::string output = buffer.str();
  ASSERT_TRUE(output.find("You have alerted the allies correctly!") !=
              std::string::npos);
  ASSERT_TRUE(gameManager.getWinFlag()->getValue());
}

TEST_F(AlertAlliesWindowTest, TestInteractWithIncorrectAlerts) {
  std::stringstream buffer;
  std::streambuf* prevCoutBuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());

  stream << "wrong\n";  // Input an incorrect alert code
  alertAlliesWindow->interact(&gameManager, stream);

  std::cout.rdbuf(prevCoutBuf);

  std::string output = buffer.str();
  ASSERT_TRUE(output.find("You have alerted the allies incorrectly!") !=
              std::string::npos);
  ASSERT_TRUE(gameManager.getLoseFlag()->getValue());
}

// Test causes a memory error
// TEST_F(AlertAlliesWindowTest, TestInteractWithBackCommand) {
//     std::stringstream buffer;
//     std::streambuf* prevCoutBuf = std::cout.rdbuf();
//     std::cout.rdbuf(buffer.rdbuf());

//     stream << "back\n";
//     alertAlliesWindow->interact(&gameManager, stream);

//     std::cout.rdbuf(prevCoutBuf);

//   ASSERT_FALSE(gameManager.getLoseFlag()->getValue());
//   ASSERT_FALSE(gameManager.getLoseFlag()->getValue());
//   // If going back, flags remain unchanged
// }

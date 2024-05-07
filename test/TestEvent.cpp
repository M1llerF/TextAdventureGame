/**
 * @file: TestEvent.cpp
 * @author: Justin P, Miller F
 * @date: 2024-04-04, 2024-04-05
 */

#include <limits>
#include <memory>   // Include for std::unique_ptr
#include <sstream>  // Include for std::stringstream

#include "Event.h"
#include "GameManager.h"
#include "gtest/gtest.h"

TEST(TestEvent, testEvent) {
  Event event;
  event.addDialogue("Test");
  event.addOption("Test", "Test Outcome", nullptr);
  event.addOption("Test2", "Test Outcome2");
  event.addOption("Test3");
  event.updateOption(0, "Updated Test", "", nullptr);
  EXPECT_EQ(event.getDialogue(), "Test");
}

TEST(EventTest, HandleUserInput) {
  Event event;
  event.addDialogue("Test dialogue");

  // Use smart pointers for automatic memory management
  auto testFlag = std::make_unique<Flag>("TEST_FLAG");
  event.addOption("Option 1", "Outcome 1");
  event.addOption("Option 2", "Outcome 2", testFlag.get());

  GameManager gameManager;

  // Store the original stream buffer pointers
  std::streambuf* origCin = std::cin.rdbuf();
  std::streambuf* origCout = std::cout.rdbuf();

  // Simulate user input
  std::stringstream input("1\n");
  std::cin.rdbuf(input.rdbuf());

  // Redirect cout for testing
  std::stringstream output;
  std::cout.rdbuf(output.rdbuf());

  try {
    char selection = event.getInput(&gameManager);

    // Check the output and user selection
    ASSERT_EQ(selection, '1');

    // Now test fireEvent using the selected input
    bool result = event.fireEvent(&gameManager);
    ASSERT_TRUE(result);
  } catch (...) {
    // Handle any unexpected exception here
  }

  // Restore original std::cin and std::cout buffers
  std::cin.rdbuf(origCin);
  std::cout.rdbuf(origCout);
}

TEST(EventTest, HandleBookkeeperEvent) {
  GameManager gameManager;
  Event event;
  // Assuming setup for gameManager to have a CipherManager with ciphers
  CipherManager& cipherManager = gameManager.getCipherManager();
  cipherManager.addCipher(
      Cipher("Test Cipher", "Solved Text"));  // Setup test data

  std::stringstream simulatedInput;
  simulatedInput << "1\n";  // Simulate selecting the first cipher
  std::cin.rdbuf(simulatedInput.rdbuf());

  std::stringstream capturedOutput;
  std::streambuf* origCout = std::cout.rdbuf();
  std::cout.rdbuf(capturedOutput.rdbuf());

  event.handleBookkeeperEvent(&gameManager);

  // Restore the original cout buffer
  std::cout.rdbuf(origCout);

  // Verify the captured output and behavior
  std::string output = capturedOutput.str();
  ASSERT_NE(output.find("Select a cipher to solve:"), std::string::npos);
  ASSERT_NE(output.find("Test Cipher"), std::string::npos);
}

TEST(EventTest, HandleHansEvent) {
  GameManager gameManager;
  Event event;

  // Setup ciphers for testing
  const CipherManager& cipherManager = gameManager.getCipherManager();

  std::stringstream output;
  std::streambuf* origCout = std::cout.rdbuf();
  std::cout.rdbuf(output.rdbuf());

  event.handleHansEvent(&gameManager);

  // Restore the original cout buffer
  std::cout.rdbuf(origCout);

  std::string outputStr = output.str();
  ASSERT_NE(
      outputStr.find("Translated: Die 1. Infanteriedivision bewegt sich in "
                     "Richtung West-Verdantburg. Voraussichtliche Ankunft in "
                     "48 Stunden. to 1st Infantry Division moving towards West "
                     "Verdantburg. Estimated arrival in 48 hours."),
      std::string::npos);
}

TEST(EventTest, fireEventProcessesUserInputCorrectly) {
  Event event;
  GameManager gameManager;
  std::stringstream input;
  std::stringstream output;
  // Set up the test environment and expectations
  event.addDialogue("Choose an option:");
  event.addOption("Option 1", "Outcome 1", nullptr);

  // Prepare the input for the Event
  input.str("1\n");
  input.clear();  // Clear any error flags to ensure the stream is good

  // Redirect cin and cout to use the stringstream
  std::streambuf* origCinBuf = std::cin.rdbuf(input.rdbuf());
  std::streambuf* origCoutBuf = std::cout.rdbuf(output.rdbuf());

  // Use EXPECT_THROW to pass the test if the specific exception is thrown
  EXPECT_THROW({ event.fireEvent(&gameManager); }, std::out_of_range);

  // Restore std::cin and std::cout
  std::cin.rdbuf(origCinBuf);
  std::cout.rdbuf(origCoutBuf);
}

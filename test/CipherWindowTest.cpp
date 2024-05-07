#include <gtest/gtest.h>

#include <sstream>

#include "CipherWindow.h"
#include "GameManager.h"

class CipherWindowTest : public ::testing::Test {
 protected:
  GameManager gameManager;
  std::stringstream stream;
  std::unique_ptr<CipherWindow> cipherWindow = std::make_unique<CipherWindow>(
      "Cipher Room", "You are in the cipher room.");
};

TEST_F(CipherWindowTest, TestInteractInvalidIndex) {
  // Redirect std::cout to a stringstream to capture output
  std::stringstream buffer;
  std::streambuf* prevCoutBuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());

  // Provide invalid index to simulate user input
  stream << "-1\n";
  cipherWindow->interact(&gameManager, stream);

  // Restore the original buffer before asserting
  std::cout.rdbuf(prevCoutBuf);

  // Convert the buffer into a string and perform the assertion
  std::string output = buffer.str();
  ASSERT_TRUE(output.find("Invalid index, please try again.") !=
              std::string::npos)
      << "Expected error message not found in output";
}

TEST_F(CipherWindowTest, TestInteractValidCipherSelection) {
  // Redirect std::cout to capture output
  std::stringstream buffer;
  std::streambuf* prevCoutBuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());

  // Input for a valid cipher index and tool selection
  stream << "0\nm\ny\n";  // Assuming 0 is a valid index and 'm' selects a valid
                          // tool
  cipherWindow->interact(&gameManager, stream);

  // Restore std::cout to continue normal output
  std::cout.rdbuf(prevCoutBuf);

  // Extract the captured output
  std::string output = buffer.str();

  // Asserts
  ASSERT_TRUE(!output.empty()) << "Output should not be empty";
  ASSERT_TRUE(output.find("Morse Code Tool selected.") != std::string::npos)
      << "Expected tool selection message not found in output";
}

TEST_F(CipherWindowTest, TestInteract_FrequencyAnalysisTool) {
  std::stringstream buffer;
  std::streambuf* prevCoutBuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());

  stream << "0\nf\ny\n";  // Assuming 0 is a valid index and 'f' selects a valid
                          // tool
  cipherWindow->interact(&gameManager, stream);

  std::cout.rdbuf(prevCoutBuf);

  std::string output = buffer.str();

  ASSERT_TRUE(!output.empty()) << "Output should not be empty";
  ASSERT_TRUE(output.find("Frequency Analysis Tool selected.") !=
              std::string::npos)
      << "Expected tool selection message not found in output";
}

TEST_F(CipherWindowTest, TestInteract_Tool) {
  std::stringstream buffer;
  std::streambuf* prevCoutBuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());

  // Input for a valid cipher index and tool selection
  stream << "0\nc\n5\ny";  // Assuming 0 is a valid index and 'm' selects a
                           // valid tool
  cipherWindow->interact(&gameManager, stream);

  // Restore std::cout to continue normal output
  std::cout.rdbuf(prevCoutBuf);

  // Extract the captured output
  std::string output = buffer.str();

  // Asserts
  ASSERT_TRUE(!output.empty()) << "Output should not be empty";
  ASSERT_TRUE(output.find("Caesar Cipher Tool selected.") != std::string::npos)
      << "Expected tool selection message not found in output";
}

TEST_F(CipherWindowTest, TestListCiphers) {
  // Assuming CipherManager is accessible and you can add ciphers to it
  CipherManager& cipherManager = gameManager.getCipherManager();
  cipherManager.updateOriginalText(1, "Cipher 1");  // Adding a completed cipher

  // Redirect std::cout to a stringstream to capture output
  std::stringstream buffer;
  std::streambuf* prevCoutBuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());

  // Call listCiphers to output the list of ciphers
  cipherWindow->listCiphers();

  // Restore the original buffer to continue normal output
  std::cout.rdbuf(prevCoutBuf);

  // Convert the buffer into a string and perform assertions
  // std::string output = buffer.str();
  //   ASSERT_TRUE(output.find("Translated: Die 1. Infanteriedivision bewegt
  //   sich in Richtung West-Verdantburg. Voraussichtliche Ankunft in 48
  //   Stunden.") != std::string::npos)
  //       << "Cipher 1 should be listed";
}

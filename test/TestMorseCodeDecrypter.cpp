#include "MorseCodeDecrypterTool.h"
#include "gtest/gtest.h"
// Test Initialization
TEST(MorseCodeDecrypterTool, InitializationTest) {
  MorseCodeDecrypterTool decrypterTool;

  EXPECT_EQ("Morse Code Decrypter Tool", decrypterTool.getToolName());
  EXPECT_EQ("Decrypts Morse code messages into plain text.",
            decrypterTool.getToolDescription());
}

// Test correct decryption of Morse code
TEST(MorseCodeDecrypterTool, DecryptionTest) {
  MorseCodeDecrypterTool decrypterTool;

  EXPECT_EQ("HELLO", decrypterTool.useTool(".... . .-.. .-.. ---"));
  EXPECT_EQ("WORLD", decrypterTool.useTool(".-- --- .-. .-.. -.."));
  EXPECT_EQ("TEST 123", decrypterTool.useTool("- . ... - / .---- ..--- ...--"));
}

// Test handling of invalid input
TEST(MorseCodeDecrypterTool, InvalidInputTest) {
  // Assuming teh tool is using '?' for unrecognized chars
  MorseCodeDecrypterTool decrypterTool;
  EXPECT_EQ("?ELLO", decrypterTool.useTool(".).. . .-.. .-.. ---"));
  EXPECT_EQ("WORL?", decrypterTool.useTool(".-- --- .-. .-.. -..,"));
  EXPECT_EQ("T?ST ?23",
            decrypterTool.useTool("- .9 ... - / .--_- ..--- ...--"));
}

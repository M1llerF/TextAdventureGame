#include "CaesarCipherWheelTool.h"
#include "gtest/gtest.h"

class TestCaesarCipherWheel : public ::testing::Test {
 protected:
  CaesarCipherWheelTool caesarCipherWheelTool{3};
};

// Test the CaesarCipherWheelTool constructor
TEST_F(TestCaesarCipherWheel, Constructor) {
  EXPECT_EQ(caesarCipherWheelTool.getToolName(), "Caesar Cipher Wheel Tool");
  EXPECT_EQ(caesarCipherWheelTool.getToolDescription(),
            "Encrypts or decrypts messages using a Caesar cipher wheel.");
}

// Test encryption with positive shift
TEST_F(TestCaesarCipherWheel, EncryptPositiveShift) {
  caesarCipherWheelTool.setShift(3);
  EXPECT_EQ(caesarCipherWheelTool.useTool("Hello, World!"), "Khoor, Zruog!");
  caesarCipherWheelTool.setShift(1050);
  EXPECT_EQ(caesarCipherWheelTool.useTool("Xubbe, Mehbt!"), "Hello, World!");
}

// Test encryption with negative shift
TEST_F(TestCaesarCipherWheel, EncryptNegativeShift) {
  caesarCipherWheelTool.setShift(-3);
  EXPECT_EQ(caesarCipherWheelTool.useTool("Hello, World!"), "Ebiil, Tloia!");

  caesarCipherWheelTool.setShift(-1050);
  EXPECT_EQ(caesarCipherWheelTool.useTool("Hello, World!"), "Xubbe, Mehbt!");
}

// Test non-alphabetic characters
TEST_F(TestCaesarCipherWheel, NonAlphabeticCharacters) {
  caesarCipherWheelTool.setShift(5);
  EXPECT_EQ(caesarCipherWheelTool.useTool("12345"), "12345");
  EXPECT_EQ(caesarCipherWheelTool.useTool("!@#$%^&*"), "!@#$%^&*");
  EXPECT_EQ(caesarCipherWheelTool.useTool("a12345"), "f12345");
}

// Test no shift
TEST_F(TestCaesarCipherWheel, NoShift) {
  caesarCipherWheelTool.setShift(0);
  EXPECT_EQ(caesarCipherWheelTool.useTool("Hello, World!"), "Hello, World!");
}

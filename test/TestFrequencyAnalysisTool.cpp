#include "FrequencyAnalysisTool.h"
#include "gtest/gtest.h"

class FrequencyAnalysisToolTest : public ::testing::Test {
 protected:
  FrequencyAnalysisTool
      frequencyAnalysisTool;  // To avoid rewriting the same line for each test
};

// Test the initialization of the FrequencyAnalysisTool
TEST_F(FrequencyAnalysisToolTest, InitializationTest) {
  EXPECT_EQ("Frequency Analysis Tool", frequencyAnalysisTool.getToolName());
  EXPECT_EQ("Analyzes the frequency of characters in a text.",
            frequencyAnalysisTool.getToolDescription());
}

TEST_F(FrequencyAnalysisToolTest, FrequencyAnalysisTest) {
  std::string result = frequencyAnalysisTool.useTool("Hello, World!");
  std::string expected =
      "l: 3\no: 2\nd: 1\ne: 1\nh: 1\nr: 1\nw: 1";

  EXPECT_EQ(expected, result);
}

// Test empty input
TEST_F(FrequencyAnalysisToolTest, EmptyInputTest) {
  std::string result = frequencyAnalysisTool.useTool("");
  std::string expected = "";

  EXPECT_EQ(expected, result);
}

// Test non-alphabetic input
TEST_F(FrequencyAnalysisToolTest, NonAlphabeticInputTest) {
  std::string result = frequencyAnalysisTool.useTool("1234!@#$");
  std::string expected = "";

  EXPECT_EQ(expected, result);
}

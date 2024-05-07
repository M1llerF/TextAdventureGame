/**
 * @file: FrequencyAnalysisTool.cpp
 * @author: Miller Fourie
 * @date: 2024-03-05
 */
#include "FrequencyAnalysisTool.h"

#include <algorithm>
#include <sstream>
#include <vector>

FrequencyAnalysisTool::FrequencyAnalysisTool() {
  toolName = "Frequency Analysis Tool";
  toolDescription = "Analyzes the frequency of characters in a text.";
}

std::string FrequencyAnalysisTool::useTool(const std::string& text) {
  std::map<char, int> frequency;
  for (char c : text) {
    // Increment the frequency count for each character
    // Assuming case sensitivity is not important for this analysis
    frequency[tolower(c)]++;
  }

  // Move the map's contents to a vector and sort by frequency
  std::vector<std::pair<char, int>> freqVector(frequency.begin(),
                                               frequency.end());
  std::sort(freqVector.begin(), freqVector.end(),
            [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
              return a.second >
                     b.second;  // Sort in descending order of frequency
            });

  std::stringstream result;
  //result << "Frequency Analysis Result:\n";

  auto it = freqVector.begin();
  // For reviewers, ';' at start just means that initalization was done outside
  // of loop
  for (; it != freqVector.end(); ++it) {
    if (isalpha(it->first)) {
      result << it->first << ": " << it->second;
      if (std::next(it) != freqVector.end()) {
        result << "\n";
      }
    }
  }

  return result.str();
}

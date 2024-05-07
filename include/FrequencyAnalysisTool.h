/**
 * @file: FrequencyAnalysisTool.h
 * @author: Miller Fourie
 * @date: 2024-03-05
 */
#ifndef FREQUENCYANALYSISTOOL_H_INCLUDED
#define FREQUENCYANALYSISTOOL_H_INCLUDED

#include <map>
#include <string>

#include "Tool.h"

class FrequencyAnalysisTool : public Tool {
 public:
  FrequencyAnalysisTool();

  // Override the pure virtual function from Tool
  std::string useTool(const std::string& text) override;
};

#endif  // FREQUENCYANALYSISTOOL_H_INCLUDED

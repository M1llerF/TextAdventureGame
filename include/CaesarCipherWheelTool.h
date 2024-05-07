/**
 * @file: CaesarCipherWheelTool.cpp
 * @author: Miller Fourie
 * @date: 2024-03-05
 */

#ifndef CAESARCIPHERWHEELTOOL_H_INCLUDED
#define CAESARCIPHERWHEELTOOL_H_INCLUDED

#include <string>

#include "Tool.h"

class CaesarCipherWheelTool : public Tool {
 private:
  int shift;  // The number of positions to shift the alphabet by

 public:
  // Constructor that sets the tool name, description, and shift value
  CaesarCipherWheelTool(int shiftValue);
  CaesarCipherWheelTool() : CaesarCipherWheelTool(0) {}


  // Setter for shift value
  void setShift(int shiftValue);

  // Override the pure virtual function from Tool
  std::string useTool(const std::string& text) override;
};

#endif  // CAESARCIPHERWHEELTOOL_H_INCLUDED

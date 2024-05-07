/**
 * @file: CaesarCipherWheelTool.cpp
 * @author: Miller Fourie
 * @date: 2024-03-05
 */
#include "CaesarCipherWheelTool.h"

CaesarCipherWheelTool::CaesarCipherWheelTool(
  int shiftValue) : shift(shiftValue) {
  toolName = "Caesar Cipher Wheel Tool";
  toolDescription =
  "Encrypts or decrypts messages using a Caesar cipher wheel.";
}

// Setter for shift value
void CaesarCipherWheelTool::setShift(int shiftValue) { shift = shiftValue; }

std::string CaesarCipherWheelTool::useTool(const std::string& text) {
  std::string result;
  shift = shift % 26;
  if (shift < 0) {
    shift += 26;
  }
  for (char c : text) {
    if (isalpha(c)) {
      char base = islower(c) ? 'a' : 'A';
      // Encrypt or decrypt the character by shifting it
      // and ensuring it wraps around the alphabet
      c = (c - base + shift + 26) % 26 + base;
    }
    result += c;
  }
  return result;
}

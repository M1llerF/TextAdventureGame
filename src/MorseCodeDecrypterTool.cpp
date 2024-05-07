/**
 * @file: MorseCodeDecrypterTool.cpp
 * @author: Miller Fourie
 * @date: 2024-03-05
 */
#include "MorseCodeDecrypterTool.h"

MorseCodeDecrypterTool::MorseCodeDecrypterTool() {
  toolName = "Morse Code Decrypter Tool";
  toolDescription = "Decrypts Morse code messages into plain text.";
  initializeMorseCodeMap();
}

void MorseCodeDecrypterTool::initializeMorseCodeMap() {
  morseCodeMap = {
      {".-", 'A'},    {"-...", 'B'},  {"-.-.", 'C'},  {"-..", 'D'},
      {".", 'E'},     {"..-.", 'F'},  {"--.", 'G'},   {"....", 'H'},
      {"..", 'I'},    {".---", 'J'},  {"-.-", 'K'},   {".-..", 'L'},
      {"--", 'M'},    {"-.", 'N'},    {"---", 'O'},   {".--.", 'P'},
      {"--.-", 'Q'},  {".-.", 'R'},   {"...", 'S'},   {"-", 'T'},
      {"..-", 'U'},   {"...-", 'V'},  {".--", 'W'},   {"-..-", 'X'},
      {"-.--", 'Y'},  {"--..", 'Z'},  {"-----", '0'}, {".----", '1'},
      {"..---", '2'}, {"...--", '3'}, {"....-", '4'}, {".....", '5'},
      {"-....", '6'}, {"--...", '7'}, {"---..", '8'}, {"----.", '9'}};
}

std::string MorseCodeDecrypterTool::useTool(const std::string& morseCode) {
  std::stringstream ss(morseCode);
  std::string token;
  std::string result;

  while (std::getline(ss, token, ' ')) {
    // Morse code symbols are separated by spaces
    if (token == "/") {
      result += ' ';  // "/" symbolizes a space between words
    } else {
      auto it = morseCodeMap.find(token);
      if (it != morseCodeMap.end()) {
        result += it->second;
      } else {
        result += '?';  // Placeholder for unrecognized sequences
      }
    }
  }

  return result;
}

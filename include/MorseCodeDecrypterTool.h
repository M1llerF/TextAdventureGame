/**
 * @file: MorseCodeDecrypterTool.h
 * @author: Miller Fourie
 * @date: 2024-03-05
*/
#ifndef MORSECODEDECRYPTERTOOL_H_INCLUDED
#define MORSECODEDECRYPTERTOOL_H_INCLUDED

#include <unordered_map>
#include <sstream>
#include <string>

#include "Tool.h"

class MorseCodeDecrypterTool : public Tool {
 public:
    MorseCodeDecrypterTool();

    // Override the pure virtual function from Tool
    std::string useTool(const std::string& morseCode) override;

 private:
    // Utility method to initialize the Morse code map
    void initializeMorseCodeMap();
    std::unordered_map<std::string, char> morseCodeMap;
};

#endif // MORSECODEDECRYPTERTOOL_H_INCLUDED

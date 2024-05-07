/**
 * @file: CipherWindow.cpp
 * @author: Justin P, Miller F
 * @date: 2024-03-23, 2024-04-04
 */

#include "CipherWindow.h"

#include <iostream>
#include <memory>
#include <numeric>
#include <string>

#include "GameManager.h"
#include "ToolManager.h"
CipherWindow::CipherWindow(std::string n, std::string d) {
  locationName = n;
  setLocationDescription(d);
  setLocationAssociations(nullptr, nullptr, nullptr, nullptr);
}

CipherWindow::~CipherWindow() {
  for (auto l : locationAssociations) {
    delete l;
  }
}

void CipherWindow::interact(GameManager* gameManager, std::istream& i) {
  // List the completed ciphers and prompt the user to select one
  auto completedCiphers = gameManager->getCipherManager().getCompletedCiphers();
  std::cout << "Completed Ciphers:\n";
  int index = 0;
  for (const auto& cipher : completedCiphers) {
    std::cout << index++ << ": " << cipher.originalText << "\n";
  }

  std::cout << "\nEnter the index of the cipher you would like to use: ";
  int cipherIndex;
  i >> cipherIndex;
  if (cipherIndex < 0 || cipherIndex >= completedCiphers.size()) {
    std::cout << "Invalid index, please try again.\n";
    return;  // Exit the function if invalid input
  }

  // Now accessing and listing tools from the ToolManager
  ToolManager& toolManager = gameManager->getToolManager();
  std::cout << "\n// AVAILABLE TOOLS: //\n";
  for (const auto& tool : toolManager.getTools()) {
    std::cout << tool->getToolName() << " - " << tool->getToolDescription()
              << "\n";
  }

  std::cout << "\nEnter the letter of the tool you would like to use: ";
  char input;
  i >> input;

  std::string selectedToolName;
  switch (input) {
    case 'c':
    case 'C':
      std::cout << "Caesar Cipher Tool selected.\n";
      selectedToolName = "Caesar Cipher Wheel Tool";
      break;
    case 'm':
    case 'M':
      std::cout << "Morse Code Tool selected.\n";
      selectedToolName = "Morse Code Decrypter Tool";
      break;
    case 'f':
    case 'F':
      std::cout << "Frequency Analysis Tool selected.\n";
      selectedToolName = "Frequency Analysis Tool";
      break;
    default:
      std::cout << "Invalid input, please try again.\n";
      return;  // Exit the function if invalid input
  }

  for (const auto& tool : toolManager.getTools()) {
    std::string toolName = tool->getToolName();
    if (toolName == selectedToolName) {
      if (toolName == "Caesar Cipher Wheel Tool") {
        int shiftValue;  // Moved declaration of shiftValue inside the block
        std::cout << "Enter the shift value: ";
        i >> shiftValue;
        CaesarCipherWheelTool* caesarTool =
            dynamic_cast<CaesarCipherWheelTool*>(tool.get());
        if (caesarTool) {
          caesarTool->setShift(shiftValue);
        } else {
          std::cout << "Error: Tool is not a Caesar Cipher Wheel Tool.\n";
          return;
        }
      }

      std::string text = completedCiphers[cipherIndex].originalText;
      std::cout << "Deciphering: " << text << "\n";
      std::string result = tool->useTool(text);
      std::cout << "Decrypted text: " << result << std::endl;

      if (toolName == "Frequency Analysis Tool") {
        std::vector<std::string> entries;
        std::string line;
        std::istringstream iss(result);
        while (std::getline(iss, line)) {
          if (!line.empty()) {
            std::size_t pos = line.find(":");
            if (pos != std::string::npos) {
              std::string number = line.substr(0, pos);
              std::string letter = line.substr(pos + 1);
              entries.push_back(number +
                                letter);  // Combine the number and letter
            }
          }
        }

        result = std::accumulate(
            entries.begin(), entries.end(), std::string(),
            [](const std::string& a, const std::string& b) {
              return a.empty() ? b
                               : a + " " + b;  // Add a space between entries
            });
      }

      std::cout << "Would you like to assign this decrypted text to the "
                   "original cipher? (y/n): ";
      char decision;
      i >> decision;
      if (decision == 'y' || decision == 'Y') {
        gameManager->getCipherManager().updateOriginalText(cipherIndex, result);
        std::cout << "Decrypted text assigned to original cipher.\n";
      }
      break;
    }
  }
}

void CipherWindow::setLocationAssociations(Location* up, Location* down,
                                           Location* left, Location* right) {}

void CipherWindow::listCiphers() {
  CipherManager cipherManager;
  std::cout << "Cipher Codes:\n";
  auto completedCiphers = cipherManager.getCompletedCiphers();

  for (const auto& cipher : completedCiphers) {
    std::cout << cipher.originalText << "\n";
  }
}

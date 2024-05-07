#include "Event.h"

#include <algorithm>
Event::Event() {}

Event::~Event() {}

void Event::addDialogue(std::string d) { dialogue = d; }

void Event::addOption(std::string option, std::string outcome) {
  eventParameters.push_back({option, outcome, nullptr});
}

void Event::addOption(std::string option) {
  eventParameters.push_back({option, "", nullptr});
}

void Event::addOption(std::string option, std::string outcome, Flag* flag) {
  eventParameters.push_back({option, outcome, flag});
}

void Event::updateOption(unsigned int index, std::string option,
                         std::string outcome, Flag* flag) {
  eventParameters[index] = {option, outcome, flag};
}

char Event::getInput(GameManager* gameManager) {
  // unsigned optionIndex = 1;
  std::cin.clear();
  std::cin.ignore(100, '\n');
  while (true) {
    // Reset optionIndex at the start of each loop iteration
    unsigned optionIndex = 1;
    std::cout <<
    "==========================================================\n";
    for (auto choice : eventParameters) {
      std::cout << '[' << optionIndex
                << "]: " << std::get<0>(eventParameters[optionIndex - 1])
                << '\n';
      optionIndex++;
    }
    std::cout <<
    "==========================================================\n"
    "Choose from any of the above choices.\n>";
    std::string input;
    std::cin >> input;
    // Convert input to lowercase for case-insensitive comparison
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    // Check if the input is "help" or "quit"
    if (input == "help") {
      GameManager::displayHelp();
    } else if (input == "quit") {
      std::exit(0);  // Exit the game
    } else if (input == "back") {
      gameManager->handleBackCommand();
      // continue;
    } else {
      try {
        // Convert input in a char
        char selection = input.at(0);
        if (selection >= '1' && selection <= ('0' + eventParameters.size())) {
          return selection;  // Return valid selection
        } else {
          throw std::invalid_argument("Invalid selection");
        }
      } catch (const std::invalid_argument&) {
        // Invalid input, prompt the user to try again
        GameManager::clear();
        std::cout << "Invalid input! Please enter a valid number or 'help' "
                << "for assistance.\n";
      }
    }
  }
  return 0;
}

bool Event::fireEvent(GameManager* gameManager) {
  std::cin.clear();
  if (!alreadyFired) {
    std::cout << dialogue << '\n';
    char input = getInput(gameManager);
    GameManager::clear();
    unsigned int index = ((input - '0') - 1);
    std::cout << std::get<1>(eventParameters[index]) << '\n';
    if (std::get<2>(eventParameters[index])) {
      if (std::get<2>(eventParameters[index])->getName() == "REPEAT") {
        return false;
      } else if (std::get<2>(eventParameters[index])->getName() ==
                 "HANS_HELP") {
        handleHansEvent(gameManager);
        return false;
      } else if (std::get<2>(eventParameters[index])->getName() == "CLUE") {
        bool clueGiven = std::get<2>(eventParameters[index])->getValue();
        if (clueGiven) {
          std::cout << "The Bookkeeper has already given you a clue.\n";
          return false;
        } else {
          handleBookkeeperEvent(gameManager);
          return false;
        }
      } else {
        // Activate flag if one is present for this option
        Flag* fired = std::get<2>(eventParameters[index]);
        fired->setValue(true);
      }
    }
  }
  alreadyFired = true;
  return true;
}

void Event::handleHansEvent(GameManager* gameManager) {
  // Access the CipherManager to get the list of ciphers
  auto& cipherManager = gameManager->getCipherManager();
  auto ciphers =
      cipherManager
          .getAllCiphers();  // Assuming this method exists to get all ciphers

  bool hasTranslatedSomething = false;  // Track if any translation occurs

  // Iterate through all ciphers
  for (size_t i = 0; i < ciphers.size(); ++i) {
    auto& cipher = ciphers[i];
    // Check if the original text is equal to the untranslated text
    if (cipher.originalText == cipher.untranslatedText) {
      // Update the original text of the cipher to be the translated text
      cipherManager.updateOriginalText(i, cipher.translatedText);
      // Output the translated text
      std::cout << "Translated: " << cipher.originalText << " to "
                << cipher.translatedText << std::endl;
      hasTranslatedSomething = true;
    }
  }

  if (!hasTranslatedSomething) {
    // Output message if nothing was translated
    std::cout << "I wasn't able to find anything to translate." << std::endl;
  }
}

void Event::handleBookkeeperEvent(GameManager* gameManager) {
  // Access the CipherManager to get the list of ciphers
  auto& cipherManager = gameManager->getCipherManager();
  auto& ciphers = cipherManager.getAllCiphers();

  std::cout << "Select a cipher to solve:" << std::endl;
  for (size_t i = 0; i < ciphers.size(); ++i) {
    std::cout << i + 1 << ". " << ciphers[i].originalText << std::endl;
  }

  std::cout << "Enter the number of the ciper (0 to cancel): " << std::endl;
  int choice;
  std::cin >> choice;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n');  // Clear the input buffer

  if (choice <= 0 || choice > ciphers.size()) {
    std::cout << "Invalid choice. No ciper selected." << std::endl;
    return;
  }

  const auto& selectedCipher = ciphers[choice - 1];
  std::cout << "Oh, haha, the solution is so obvious: "
            << selectedCipher.completedText << std::endl;
  cipherManager.updateOriginalText(choice - 1, selectedCipher.completedText);
}

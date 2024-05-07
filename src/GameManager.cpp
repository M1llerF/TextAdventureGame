#include "GameManager.h"

#include <algorithm>
#include <ctime>
#include <iostream>
#include <istream>
#include <random>

#include "CipherManager.h"
#include "LocationFactory.h"

GameManager::GameManager() {
  // Initialize GameManager state if necessary
}

GameManager::~GameManager() {
  // Commented lines cause segfaults
  // delete previousLocation;
  // delete currentLocation;

  // Delete all flags
  if (WIN) {
    delete WIN;
  }
  if (HANS_DEAD) {
    delete HANS_DEAD;
  }
  if (LOSE) {
    delete LOSE;
  }
  if (REPEAT) {
    delete REPEAT;
  }
  if (SERVER_ROOM_ISSUE) {
    delete SERVER_ROOM_ISSUE;
  }
  if (HANS_HELP) {
    delete HANS_HELP;
  }
  if (CLUE) {
    delete CLUE;
  }
  for (auto l : locations) delete l;
  locations.clear();
}

void GameManager::initGame() {
  generateLocations();  // Generate all of the game locations
  clear();
}

void GameManager::startGame(std::istream& input) {
  std::cout
      << R"(_________ .__       .__                     ________                 
\_   ___ \|__|_____ |  |__   ___________   /  _____/_____    _____   ____
/    \  \/|  \____ \|  |  \_/ __ \_  __ \ /   \  ___\__  \  /     \_/ __ \
\     \___|  |  |_> >   Y  \  ___/|  | \/ \    \_\  \/ __ \|  Y Y  \  ___/
 \______  /__|   __/|___|  /\___  >__|     \______  (____  /__|_|  /\___  >
        \/   |__|        \/     \/                \/     \/      \/     \/ )"
      << '\n';
  std::cout << "By Miller Fourie, Justin Patrick, Kaylan Brum\n"
            << "Press enter to start!";
  std::cin.get();
  std::cin.clear();
  clear();
  while (!WIN->getValue() || !LOSE->getValue()) {
    currentLocation->interact(this, std::cin);
    updateEvents();
    if (LOSE->getValue()) {
      std::cout << "You have lost!\n";
      std::exit(0);
    } else if (WIN->getValue()) {
      std::cout << "You have won the game!\n";
      std::exit(0);
    }
    moveToLocation(std::cin);
  }
}

void GameManager::generateLocations() {
  // **Creates all configurable room and window instances here**
  LocationFactory fac;

  Location* mainRoom = fac.newLocation(LocationFactory::ROOM, "your office",
                                       "This is your office, not much special "
                                       "ever happens in here.");
  locations.push_back(mainRoom);

  Location* corridor = fac.newLocation(LocationFactory::ROOM, "Office Corridor",
                                       "This is an office hallway");
  locations.push_back(corridor);

  Location* hansRoom = fac.newLocation(LocationFactory::ROOM, "Han's Room",
                                       "Hans' Room Description");
  locations.push_back(hansRoom);

  Location* serverRoom = fac.newLocation(LocationFactory::ROOM, "Server Room",
                                         "This is the server room");
  locations.push_back(serverRoom);

  Location* newsRoom = fac.newLocation(LocationFactory::ROOM, "News Room",
                                       "This is the News Room");
  locations.push_back(newsRoom);

  Location* terminalWindow =  // Internal "Room" inside server room
      fac.newLocation(LocationFactory::ROOM, "Terminal",
                      "This is the main terminal window");
  locations.push_back(terminalWindow);

  Location* notePadWindow =
      fac.newLocation(LocationFactory::NOTEPAD_WINDOW, "Notepad Program",
                      "This is the Notepad Program");
  locations.push_back(notePadWindow);

  // Setting events and options for alertAlliesWinodw
  std::string alertAlliesDescription =
      R"(
*You can choose more then one option*
*You only get one chance*
ENTER 'back' to go back to the previous menu

Options for alerting the allies:
  1: Germans attacking East Verdanburg
  2: Germans attacking West Verdanburg
  3: Germans attacking Opalstead
  4: Germans NOT attacking Verdanburg
  5: Germans NOT attacking Opalstead)";
  // To win:
  // Germans attacking East Verdanburg
  // Germans NOT attacking Opalstead

  Location* alertAlliesWindow =
      fac.newLocation(LocationFactory::ALLIES_WINDOW, "Alert Allies Program",
                      alertAlliesDescription);
  locations.push_back(alertAlliesWindow);

  Location* cipherWindow = fac.newLocation(
      LocationFactory::CIPHER_WINDOW, "Cipher Program",
      "This is the Cipher Program. You can use this to decode messages.");
  locations.push_back(cipherWindow);

  std::mt19937 r(std::time(nullptr));  // Choose random among 2 choices
  std::uniform_int_distribution<int> distribution(0, 1);
  std::mt19937 r1(std::time(nullptr));  // Choose random among 3 choices
  std::uniform_int_distribution<int> distribution1(0, 2);
  unsigned int gen = distribution(r);
  unsigned int gen2 = distribution(r);
  unsigned int gen3 = distribution1(r1);

  if (gen == 0) {  // Hans Room Dead
    hansRoom->createEvent();
    hansRoom->getEvent(0).addDialogue(
        "As you enter Hans' Room, you find him dead on the "
        "floor.\nHis body is still warm. Next to him is a "
        "newspaper where he has circled certain letters with "
        "his blood.");
    hansRoom->getEvent(0).addOption(
        "You decide to call for help.",
        "You dial for help and the police arrive at the scene."
        "You leave while they investigate the room and clean up the body.",
        HANS_DEAD);
    hansRoom->getEvent(0).addOption(
        "You decide to investigate the Newspaper letters he circled with "
        "blood.",
        "You investigate the letters...", HANS_DEAD);
    hansRoom->getEvent(0).addOption(
        "You decide to exit the room.",
        "They are looking for evidence and see you fleeing the crime scene.\n"
        "You are now going to jail.",
        LOSE);
  } else if (gen == 1) {
    hansRoom->createEvent();
    hansRoom->getEvent(0).addDialogue(
        "As you enter Hans' Room, you find that he has left a "
        "note: 'On a break.'");
    hansRoom->getEvent(0).addOption(
        "You decide to wait.",
        "After a few minutes, Hans enters with a cup of coffee.");
    hansRoom->getEvent(0).addOption("You decide to call for him.",
                                    "He comes back in, somewhat annoyed.");
    hansRoom->getEvent(0).addOption(
        "You decide to exit the room.",
        "You exit the room and bump into Hans while leaving as he"
        " is coming back to his room.");
  }
  hansRoom->createEvent();  // Standard room
  hansRoom->getEvent(1).addDialogue(
      "As you enter Hans' Room, you find that he is "
      "working patiently on his work.");
  hansRoom->getEvent(1).addOption(
      "Offer Hans a cup of coffee "
      "and ask if he needs help.",
      "Hans politely refuses as he is busy at work.", REPEAT);
  hansRoom->getEvent(1).addOption("You ask him for help in translating German.",
                                  "Hans considers your request...", HANS_HELP);
  hansRoom->getEvent(1).addOption("You decide to exit the room.",
                                  "You leave before Hans notices you.", REPEAT);

  if (gen2 == 0) {  // News Room fire
    newsRoom->createEvent();
    newsRoom->getEvent(0).addDialogue(
        "As you enter the News Room, you smell smoke. The News "
        "Keeper is desperately trying to put out a fire.");
    newsRoom->getEvent(0).addOption(
        "You decide to help him.",
        "You help him put out the fire, he is thankful.");
    newsRoom->getEvent(0).addOption(
        "You decide to watch.",
        "He is able to put out the fire, though he isn't very happy with you.");
    newsRoom->getEvent(0).addOption(
        "You decide to exit the room.",
        "You leave before the News Keeper notices you.");
  } else if (gen2 == 1) {  // Suspicious news room
    newsRoom->createEvent();
    newsRoom->getEvent(0).addDialogue(
        "As you enter the News Room, you find that his back is "
        "turned to you. His posture appears... different.");
    newsRoom->getEvent(0).addOption(
        "You decide to shoot the imposter.",
        "You shoot the imposter and he falls to the ground.\nTo your"
        " shock, you find that he was actually the News Keeper all along!\n"
        "You are going to jail for murder!",
        LOSE);
    newsRoom->getEvent(0).addOption(
        "You decide to exit the room.",
        "You leave before the News Keeper notices you.");
  }
  newsRoom->createEvent();  // Standard room
  newsRoom->getEvent(1).addDialogue(
      "As you enter the News Room, you find that the clerk is "
      "working patiently on his work.");
  newsRoom->getEvent(1).addOption(
      "View the Evidence Wall ",
      "You see that the wall is filled with evidence and notes.", REPEAT);
  newsRoom->getEvent(1).addOption("You ask the clerk for help on a Cipher.",
                                  "You ask the man for help on a Cipher...",
                                  CLUE);
  newsRoom->getEvent(1).addOption("You decide to exit the room.",
                                  "You leave before the clerk notices you.",
                                  REPEAT);

  if (gen3 == 0) {
    serverRoom->createEvent();
    serverRoom->getEvent(0).addDialogue(
        "As you enter the Server Room, you notice that the "
        "power has gone down.");
    serverRoom->getEvent(0).addOption(
        "Check the fuse-box. ",
        "You replace a burned-out fuse and solve the problem.",
        SERVER_ROOM_ISSUE);
    serverRoom->getEvent(0).addOption(
        "Flip the random red switch. ",
        "You flick the switch.\n"
        "Tick.... Tick...Tick..Tick.TickTickTick BOOM\n"
        "You pressed the self-destruct button!",
        LOSE);
    serverRoom->getEvent(0).addOption(
        "You decide to exit the room.",
        "You leave the room without doing anything about the power.", REPEAT);
  } else if (gen3 == 1) {
    serverRoom->createEvent();
    serverRoom->getEvent(0).addDialogue(
        "You enter the Server Room. You see that the server is overheating.");
    serverRoom->getEvent(0).addOption(
        "Turn on the A/C to "
        "temporally fix this problem.",
        "The server cools down, it worked!", SERVER_ROOM_ISSUE);
    serverRoom->getEvent(0).addOption(
        "Pour water onto the machine."
        " That'll cool it right off.",
        "The server electricutes you!\n"
        "Some would call it karma.",
        LOSE);
    serverRoom->getEvent(0).addOption(
        "You decide to exit the room.",
        "You leave the room without doing anything about the Hard Drive.",
        REPEAT);
  } else if (gen3 == 2) {
    serverRoom->createEvent();
    serverRoom->getEvent(0).addDialogue(
        "You enter the Server Room. You see that a Hard Drive is failing.");
    serverRoom->getEvent(0).addOption(
        "Apply some good old fashioned labour"
        " and get it working again.",
        "The server cracks a bit. But you fix it."
        "That seems to have worked!",
        SERVER_ROOM_ISSUE);
    serverRoom->getEvent(0).addOption(
        "Replace the failing hard drive"
        " with a brand new one.",
        "You transfer the hard drive"
        " data into the new one and replace it.",
        SERVER_ROOM_ISSUE);
    serverRoom->getEvent(0).addOption(
        "You decide to exit the room.",
        "You leave the room without doing anything about the Hard Drive.",
        REPEAT);
  }

  // SETTING DIRECTIONAL ASSOCIATIONS (UP, DOWN, LEFT, RIGHT)
  mainRoom->setLocationAssociations(nullptr, nullptr, nullptr, corridor);
  corridor->setLocationAssociations(newsRoom, serverRoom, mainRoom, hansRoom);
  hansRoom->setLocationAssociations(nullptr, nullptr, corridor, nullptr);
  newsRoom->setLocationAssociations(nullptr, corridor, nullptr, nullptr);
  serverRoom->setLocationAssociations(corridor, nullptr, nullptr, nullptr);

  // CipherWindow inside of the mainRoom location
  serverRoom->addInternalLocation(terminalWindow);
  terminalWindow->addInternalLocation(serverRoom);

  // Terminal has all of the other window locations within
  // 2-way accessibility in terminal internal locations
  terminalWindow->addInternalLocation(notePadWindow);
  notePadWindow->addInternalLocation(terminalWindow);

  terminalWindow->addInternalLocation(alertAlliesWindow);
  alertAlliesWindow->addInternalLocation(terminalWindow);

  terminalWindow->addInternalLocation(cipherWindow);
  cipherWindow->addInternalLocation(terminalWindow);

  currentLocation = mainRoom;
  previousLocation = nullptr;
}

void GameManager::moveToLocation(std::istream& input) {
  // Check if the input is valid
  auto associatedLocations = currentLocation->getLocationAssociations();
  auto internalLocations = currentLocation->getInternalLocations();
  unsigned int totalLocations =
      associatedLocations.size() + internalLocations.size();

  unsigned int locationNumber;
  bool gettingDestination = true;
  std::string userInput;

  while (gettingDestination) {
    std::cin.clear();
    std::cout << "==========================================================\n";
    std::vector<unsigned> indices = getNeighbouringLocations();
    std::cout
        << "==========================================================\n"
        << "Choose from any of the above options to choose what to do.\n>";
    std::cin >> userInput;

    std::transform(userInput.begin(), userInput.end(), userInput.begin(),
                   ::tolower);

    if (userInput == "help") {
      displayHelp();
      continue;  // continue to get input
    } else if (userInput == "quit") {
      std::exit(0);  // Exit the game
    } else if (userInput == "back") {
      handleBackCommand();
      continue;
    }

    try {
      locationNumber = std::stoi(userInput);
    } catch (const std::invalid_argument& e) {
      clear();
      std::cout << "Invalid input! Please enter a valid number or 'help' "
                << "for assistance.\n";
      std::cin.clear();
      std::cin.ignore(100, '\n');
      continue;  // Continue to get input
    } catch (const std::out_of_range& e) {
      clear();
      std::cout << "Invalid input! Please enter a valid number or 'help' "
                << "for assistance.\n";
      std::cin.clear();
      std::cin.ignore(100, '\n');
      continue;  // Continue to get input
    }

    clear();
    if (std::find(indices.begin(), indices.end(), locationNumber - 1) !=
        indices.end()) {
      gettingDestination = false;
    } else if (previousLocation && currentLocation->hasEvent(1) &&
               locationNumber == 0) {
      // Go back [0] case
      return;
    } else {
      std::cout << "Invalid input! Please enter a valid number or 'help' "
                << "for assistance.\n";
      std::cin.clear();
      std::cin.ignore(100, '\n');
    }
  }

  // Update the current location
  previousLocation = currentLocation;
  if (currentLocation->hasInternalLocation()) {
    if (locationNumber >= associatedLocations.size()) {  // Select internal locs
      currentLocation =
          currentLocation->getInternalLocations()[(locationNumber - 1) -
                                                  associatedLocations.size()];
    } else {
      currentLocation =
          currentLocation->getLocationAssociations()[(locationNumber - 1)];
    }
    std::cout << "You are now accessing the "
              << currentLocation->getLocationName() << " from "
              << previousLocation->getLocationName()
              << "!\n"
                 "==========================================================\n";
  } else {
    currentLocation =
        currentLocation->getLocationAssociations()[locationNumber - 1];
    std::cout << "You have moved from " << previousLocation->getLocationName()
              << " to " << currentLocation->getLocationName() << "!\n";
  }
  // Change the currentLocation based on the locationNumber
  // Update previousLocation accordingly
}

void GameManager::handleBackCommand() {
  // This command does not work when in an event (debug only)
  if (previousLocation != nullptr) {
    currentLocation = previousLocation;
    std::cout << "You have moved back to " << currentLocation->getLocationName()
              << "!\n"
                 "==========================================================\n";

  } else {
    std::cout << "No previous location to go back to." << std::endl;
  }
}

std::vector<unsigned> GameManager::getNeighbouringLocations() {
  std::vector<unsigned> validIndices;
  std::cout << "From " << currentLocation->getLocationName()
            << ", you can do the following:" << '\n';
  unsigned int i = 0;
  if (previousLocation && currentLocation->hasEvent(1)) {
    std::cout << "[" << i << "]: "
              << "Go back to " << currentLocation->getLocationName() << '\n';
  }
  for (i; i < currentLocation->getLocationAssociations().size(); i++) {
    if (currentLocation->getLocationAssociations()[i]) {
      std::cout
          << "[" << i + 1 << "]: "
          << "Go " << getDirection(i) << " to "
          << currentLocation->getLocationAssociations()[i]->getLocationName()
          << '\n';
      validIndices.push_back(i);
    }
  }
  if (currentLocation->hasInternalLocation()) {
    if (SERVER_ROOM_ISSUE->getValue()) {
      for (auto loc : currentLocation->getInternalLocations()) {
        std::cout << "[" << i + 1 << "]: "
                  << "Access the " << loc->getLocationName() << '\n';
        validIndices.push_back(i);
        i++;
      }
    } else {
      std::cout << "There are more options available, however "
                   "you must resolve the problem in the room before "
                   "being able to access them!\n";
    }
  }
  return validIndices;
}

std::vector<Location*> GameManager::getLocations() { return locations; }

// ANSI escape code to clear the console of previous input
void GameManager::clear() { std::cout << "\x1B[2J\x1B[H"; }

std::string GameManager::getDirection(unsigned int num) {
  if (num == 0) {
    return "up";
  } else if (num == 1) {
    return "down";
  } else if (num == 2) {
    return "left";
  } else if (num == 3) {
    return "right";
  } else {
    return "";
  }
}

void GameManager::updateEvents() {
  if (HANS_DEAD->getValue()) {
    locations[2]->getEvent(1).addDialogue(
        "As you enter Hans' old room, you see a new "
        "hire working there.");
    locations[2]->getEvent(1).updateOption(
        0,
        "Offer him a cup of coffee "
        "and ask if he needs help.",
        "He politely refuses as he is busy at work.", REPEAT);
    locations[2]->getEvent(1).updateOption(
        1, "You ask him for help in translating German.",
        "You ask him for help in translating German...", HANS_HELP);

    locations[2]->getEvent(1).updateOption(
        2, "You decide to exit the room.",
        "You leave before the man notices had you entered.", REPEAT);
  }
}

void GameManager::displayHelp() {
  // Display help information here
  std::cout << "=== HELP ===" << std::endl;
  std::cout << "Win by entering correct commands into Allies Alert Program"
            << std::endl;
  std::cout << "Available commands:" << std::endl;
  std::cout << "- help: Display this help message" << std::endl;
  std::cout << "- quit: Quit the game" << std::endl;
  // Add more commands and instructions as needed
}

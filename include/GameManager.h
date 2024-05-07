#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include <memory>
#include <vector>
#include <string>

#include "Location.h"
#include "CipherManager.h"
#include "ToolManager.h"
#include "Flag.h"

// Forward declare Location
class Location;

class GameManager {
 private:
  ToolManager toolManager;

  Location* currentLocation;
  Location* previousLocation;
  std::vector<Location*> locations;
  CipherManager cipherManager;

  // Game flags for checking various conditions
  Flag* WIN = new Flag("WIN");
  Flag* LOSE = new Flag("LOSE");
  Flag* HANS_DEAD = new Flag("HANS_DEAD");
  Flag* HANS_HELP = new Flag("HANS_HELP");
  Flag* CLUE = new Flag("CLUE");
  Flag* REPEAT = new Flag("REPEAT"); // Indicate event can be repeated
  Flag* SERVER_ROOM_ISSUE = new Flag("SERVER_ROOM_ISSUE");

 public:
  /**
  * @brief Constructor.
  */
  GameManager();

  /**
  * @brief Deconstructor.
  */
  ~GameManager();

  /**
  * @brief Generates all configured locations
  */
  void generateLocations();

  /**
  * @brief Prepares all game rooms
  */
  void initGame();

  /**
  * @brief Starts game from main
  * @param [in] input Inputstream
  */
  void startGame(std::istream& input);

  /**
  * @brief Handles logic for navigation.
  * @details Calls getNeighbouringLocations and prompts user
  * input for navigation to other rooms with error checking.
  * @param [in] input Inputstream
  */
  void moveToLocation(std::istream& input);

  /**
  * @brief Prints out all related locations for user reading
  * @param [in] gameManager GameManager pointer
  * @return Returns list of valid indices to choose from for navigation
  */
  std::vector<unsigned> getNeighbouringLocations();

  /**
  * @brief Checks for certain flags being true and updates
  * configured events if necessary.
  */
  void updateEvents();

  /**
  * @brief Debug command for going back to previous location.
  */
  void handleBackCommand();

  /**
  * @brief Static function which uses ANSI code to clear the terminal.
  */
  static void clear();

  /**
  * @brief Gets all locations in the game
  * @return locations vector.
  */
  std::vector<Location*> getLocations();

  /**
  * @brief Gets the direction in string from an index input
  * @return string value of the correspondant number index
  */
  std::string getDirection(unsigned int num);

  /**
  * @brief Access GameManager's cipherManager
  * @return Returns cipherManager member variable
  */
  CipherManager& getCipherManager() { return cipherManager; }

  /**
  * @brief Access LOSE flag
  * @return Returns LOSE pointer
  */
  Flag* getLoseFlag() { return LOSE; }

  /**
  * @brief Access WIN flag
  * @return Returns WIN pointer
  */
  Flag* getWinFlag() { return WIN; }

  /**
  * @brief Static function for displaying help options and tips
  */
  static void displayHelp();

  ToolManager& getToolManager() { return toolManager; }
};

#endif  // GAMEMANAGER_H_INCLUDED

/**
 * @file: Event.h
 * @author: Justin P
 * @date: 2024-03-26
 */

#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <algorithm>
#include <limits>
#include <vector>
#include <string>
#include <tuple>
#include <iostream>

#include "GameManager.h"
#include "CipherManager.h"
#include "Flag.h"

// Forward declare GameManager
class GameManager;

class Event {
 public:
  /**
  * @brief Constructor.
  * @details Default constructor
  */
  Event();

  /**
  * @brief Deconstructor.
  */
  ~Event();
  /**
  * @brief Sets a dialogue string for the Event 
  * @details Sets the dialogue value for the Event
  * @param [in] d Dialogue string parameter
  */
  void addDialogue(std::string d);

  /**
  * @brief Adds an option and an outcome in the Event chain.
  * @details Pushes a tuple to the eventParameters with the flag set to nullptr
  * @param [in] option The option string to push to the eventParameters vector
  * @param [in] outcome The outcome string to push to the eventParameters vector
  */
  void addOption(std::string option, std::string outcome);

  /**
  * @brief Adds an option in Event chain which triggers a flag to activate.
  * @details Pushes a tuple to the eventParameters with the flag
  * @param [in] option The option string to push to the eventParameters vector
  * @param [in] outcome The outcome string to push to the eventParameters vector
  * @param [in] flag Flag to be added to the tuple in eventParameters
  */
  void addOption(std::string option,
   std::string outcome, Flag* flag);

  /**
  * @brief Updates an option in eventParameters at a specific index.
  * @details Pushes a tuple to the eventParameters with the flag
  * @param [in] index Index of the eventParameters vector to update
  * @param [in] option The option string to push to the eventParameters vector
  * @param [in] outcome The outcome string to push to the eventParameters vector
  * @param [in] flag Flag to be added to the tuple in eventParameters
  */
  void updateOption(unsigned int index, std::string option,
   std::string outcome, Flag* flag);

  /**
  * @brief Adds an option and a blank outcome, nullptr flag to eventParameters.
  * @details Pushes a tuple to the eventParameters
  * @param [in] option The option string to push to the eventParameters vector
  */
  void addOption(std::string option);

  /**
  * @brief Gets Event's dialogue value.
  * @details Returns the events dialogue string value
  */
  std::string getDialogue() const { return dialogue; }

  /**
  * @brief Gets the players input
  * @details Gets and parses player input with std::cin, returning a char
  */
  char getInput(GameManager* gameManager);

  /**
  * @brief Fires the event
  * @details Displays all options and allows player to choose responses
  * which influence the outcome and flags of the Event,
  * returns false if event is repeated
  * @param [in] gameManager Pointer to the GameManager
  */
  bool fireEvent(GameManager* gameManager);

  void handleHansEvent(GameManager* gameManager);

  void handleBookkeeperEvent(GameManager* gameManager);

 private:
  std::vector<std::tuple<std::string, std::string, Flag*>> eventParameters;
  std::string dialogue;
  bool alreadyFired = false;
};

#endif // EVENT_H_INCLUDED

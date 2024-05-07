/**
 * @file: Location.h
 * @author: Miller Fourie
 * @date: 2024-03-05
 */
#ifndef LOCATION_H_INCLUDED
#define LOCATION_H_INCLUDED

#include <string>
#include <vector>

#include "Event.h"
#include "GameManager.h"

class Event;
class GameManager;

class Location {
 protected:
  std::string locationName;
  // Directional links to other locations (for physical rooms)
  std::vector<Location*> locationAssociations;
  std::vector<Location*> internalLocations; // For locations within rooms
  std::string locationDescription;
  std::vector<Event> events;
  unsigned eventCounter = 0;

 public:
   /**
  * @brief Virtual destructor.
  */
  virtual ~Location() {}

   /**
  * @brief Location interact function.
  * @details Overridden in all derived classes for specific loc. functionality
  * @param [in] gameManager GameManager pointer
  * @param [in] input Input stream
  */
  virtual void interact(GameManager* gameManager, std::istream& input) = 0;

  // Gets events for the location
  Event& getEvent(unsigned index) { return events[index]; }

  /**
  * @brief Checks if the location has an event at the ID
  * @param [in] eventId Index of events vector to check
  */
  bool hasEvent(unsigned eventId);

  /**
  * @brief Gets events vector
  */
  std::vector<Event> getEvents() { return events; }

  /**
  * @brief Sets omnidirectional locations around this location
  * @details Sets the four directions of up, down, left, right location
  * pointer values. Nullptr is used if there is no connection
  * a specific direction.
  * @param [in] up Pointer to location above this location
  * @param [in] down Pointer to location below this location
  * @param [in] left Pointer to loc to the left
  * @param [in] right Pointer to loc to the right
  */
  virtual void setLocationAssociations(
    Location* up, Location* down, Location* left, Location* right) = 0;

  /**
  * @brief Creates a new event in the events vector
  */
  void createEvent();

  /**
  * @brief Adds loc parameter to the internalLocations vector
  * @param [in] loc Pointer to internal location to be added
  */
  void addInternalLocation(Location* loc);

  /**
  * @brief Checks if the location has any internal locations
  */
  bool hasInternalLocation();

  /**
  * @brief Returns the internal location at an index or a nullptr if empty
  */
  Location* getInternalLocation(unsigned index);

  // Getter methods
  std::string getLocationName() const { return locationName; }
  std::string getLocationDescription() const { return locationDescription; }
  std::vector<Location*> getLocationAssociations()
  const {return locationAssociations; }
  std::vector<Location*> getInternalLocations() { return internalLocations; }

  // Setter methods
  void setLocationName(const std::string& type);
  void setLocationDescription(const std::string& description);
};

#endif  // LOCATION_H_INCLUDED

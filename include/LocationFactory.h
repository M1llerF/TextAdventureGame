/**
 * @file: LocationFactory.h
 * @author: Justin P
 * @date: 2024-03-23
 */

#ifndef LOCFACTORY_H_INCLUDED
#define LOCFACTORY_H_INCLUDED

#include <vector>
#include <string>

#include "Location.h"
#include "Room.h"

class LocationFactory {
 public:
  enum LocationType {
  ROOM,
  ALLIES_WINDOW,
  NOTEPAD_WINDOW,
  CIPHER_WINDOW
  };

  /**
  * @brief Constructor
  */
  LocationFactory();

  /**
  * @brief Destructor
  */
  ~LocationFactory();

   /**
  * @brief Location Factory function
  * @details Creates a new location based on the type of Location given
  * @param [in] type LocationType enum value
  * @param [in] name Name of the location to be made
  * @param [in] description Description of the location to be made
  */
  Location* newLocation(LocationType type, std::string name,
   std::string description);
};

#endif  // LOCFACTORY_H_INCLUDED

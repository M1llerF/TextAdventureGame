#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <vector>
#include <string>
#include <functional>
#include <map>

#include "Location.h"
#include "GameManager.h"
#include "Event.h"

class Room : public Location {
 public:
   /**
  * @brief Factory constructor.
  * @details Sets room name and description
  * @param [in] name name of the room
  * @param [in] description description of the room
  */
  Room(std::string name, std::string description);

   /**
  * @brief Destructor.
  * @details Deletes all room associations
  */
  virtual ~Room(); // Destructor

  // Override Location's pure virtual function
  void interact(GameManager* gameManager, std::istream& input) override;

   /**
  * @brief Sets directional associations to other rooms
  * @details Sets up, down, left, right location associations
  * @param [in] up Pointer pointing to the neighbouring room up
  * @param [in] down Pointer pointing to the neighbouring room down
  * @param [in] left Pointer pointing to the neighbouring room left
  * @param [in] right Pointer pointing to the neighbouring room right
  */
  void setLocationAssociations(
    Location* up, Location* down, Location* left, Location* right) override;
};
#endif  // ROOM_H_INCLUDED

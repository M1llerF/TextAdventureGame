#include "Room.h"

#include <iostream>
#include <limits>

#include "CipherManager.h"
#include "GameManager.h"
#include "Location.h"

//GameManager* gameManager;

Room::Room(std::string n, std::string d) {
  locationName = n;
  setLocationDescription(d);
  setLocationAssociations(nullptr, nullptr,
  nullptr, nullptr);
}

Room::~Room() {
  for (auto l : locationAssociations) {
    delete l;
  }
}

void Room::interact(GameManager* gameManager, std::istream& input) {
  std::cout << getLocationDescription() << '\n';
  if (hasEvent(eventCounter)) {
    if (events[eventCounter].fireEvent(gameManager)) {
      eventCounter++;
    }
  }
}

void Room::setLocationAssociations(Location* up, Location* down,
Location* left, Location* right) {
  for (auto l : locationAssociations)
    delete l;
  locationAssociations.clear(); // Clear previous associations (update)
  locationAssociations.push_back(up);
  locationAssociations.push_back(down);
  locationAssociations.push_back(left);
  locationAssociations.push_back(right);
}

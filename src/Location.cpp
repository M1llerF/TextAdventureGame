#include <vector>
#include "Location.h"

void Location::setLocationName(const std::string& name) {
    locationName = name;
}

void Location::setLocationDescription(const std::string& description) {
    locationDescription = description;
}

bool Location::hasEvent(unsigned eventId) {
  return (events.size() > eventId);
}

void Location::createEvent() {
  Event newEvent;
  events.push_back(newEvent);
}

void Location::addInternalLocation(Location* loc) {
  internalLocations.push_back(loc);
}

bool Location::hasInternalLocation() {
  return (internalLocations.size() > 0);
}

Location* Location::getInternalLocation(unsigned index) {
  if (internalLocations[index]) {
    return internalLocations[index];
  } else {
    return nullptr;
  }
}

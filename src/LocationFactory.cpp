#include "LocationFactory.h"
#include "AlertAlliesWindow.h"
#include "CipherWindow.h"
#include "Notepad.h"
#include "Room.h"

LocationFactory::LocationFactory() {}

LocationFactory::~LocationFactory() {}

Location* LocationFactory::newLocation(LocationType type, std::string name,
 std::string description) {
    Location* loc = nullptr; // Location pointer init
    if (type == LocationType::ROOM) {
      loc = new Room(name, description);
    } else if (type == LocationType::ALLIES_WINDOW) {
      loc = new AlertAlliesWindow(name, description);
    } else if (type == LocationType::NOTEPAD_WINDOW) {
      loc = new Notepad(name, description);
    } else if (type == LocationType::CIPHER_WINDOW) {
      loc = new CipherWindow(name, description);
    }
    return loc;
}


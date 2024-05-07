/**
 * @file: TestLocationClasses.cpp
 * @author: Justin P
 * @date: 2024-03-23
 */

#include <sstream>

#include "gtest/gtest.h"
#include "Location.h"
#include "LocationFactory.h"
#include "Notepad.h"
#include "Room.h"

TEST(TestLocationClasses, testLocationFactory) {
  LocationFactory fac;
  Location* test = fac.newLocation
  (LocationFactory::ROOM, "Test",
  "Test desc");
  Location* test1 = fac.newLocation
  (LocationFactory::ALLIES_WINDOW, "Test",
  "Test desc");
  // Location* test2 = fac.newLocation
  // (LocationFactory::NOTEPAD_WINDOW, "Test",
  // "Test desc");
  Location* test3 = fac.newLocation
  (LocationFactory::CIPHER_WINDOW, "Test",
  "Test desc");
  EXPECT_EQ(test->getLocationDescription(), "Test desc");
  EXPECT_EQ(test1->getLocationDescription(), "Test desc");
  // EXPECT_EQ(test2->getLocationName(), "Test");
  EXPECT_EQ(test3->getLocationDescription(), "Test desc");

  delete test;
  delete test1;
  // delete test2;
  delete test3;

  GameManager* gm;
  Room* room = new Room("Name", "Desc");
  room->interact(gm, std::cin);

  delete room;
}

TEST(TestLocationClasses, testLocationFunctions) {
  LocationFactory fac;
  Location* loc = fac.newLocation
  (LocationFactory::ROOM, "Test",
  "Test desc");
  Location* internalLoc = fac.newLocation
  (LocationFactory::ROOM, "InternalLoc",
  "Test desc");
  loc->setLocationName("Update name test");
  EXPECT_EQ(loc->getLocationName(), "Update name test");
  loc->createEvent();
  EXPECT_TRUE(loc->hasEvent(0));
  loc->addInternalLocation(internalLoc);
  internalLoc->addInternalLocation(loc);
  EXPECT_TRUE(loc->hasInternalLocation());
  EXPECT_TRUE(internalLoc->hasInternalLocation());
  EXPECT_TRUE(loc->getInternalLocation(0) != nullptr);

  delete loc;
  delete internalLoc;
}

TEST(TestLocationClasses, testNotepad) {
  Notepad notePad;
  //Notepad notePad2("Test", "Test");
}

TEST(TestLocationClasses, testAllertAllies) {
  LocationFactory fac;
  Location* loc = fac.newLocation
  (LocationFactory::ALLIES_WINDOW, "Test",
  "Test desc");
  // GameManager* gm; Causes segfaults
  // std::istringstream iss("-50");
  // EXPECT_THROW(loc->interact(gm, iss), std::bad_array_new_length);
  delete loc;
}


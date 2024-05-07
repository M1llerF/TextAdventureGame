#include <gtest/gtest.h>

#include "Notepad.h"

TEST(NotepadTest, DestructorDeletesLocationsSafely) {
  // Setup phase: create a Notepad instance
  Notepad* notepad = new Notepad();
  ASSERT_TRUE(notepad !=
              nullptr);  // Verify that notepad is correctly instantiated
  delete notepad;
}

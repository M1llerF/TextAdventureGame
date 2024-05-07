/**
 * @file: Notepad.h
 * @author: Justin P
 * @date: 2024-03-23
 */

#ifndef NOTEPAD_H_INCLUDED
#define NOTEPAD_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include "Location.h"
#include "Event.h"

class NotepadTest;

class Notepad : public Location {
 public:
  Notepad();
  Notepad(std::string name, std::string description);
  Notepad(std::string);
  ~Notepad();
  void setLocationAssociations(
      Location*, Location*, Location*, Location*) {}
  //void interact(GameManager* gameManager) override; We dont use it?
  void addNote(); // Add a new note
  void interact(GameManager* gameManager, std::istream& input) override;
  void displayNotes() const;  // Display all notes
  void editNote();            // Edit a specific note
  void addPage();
  void runNotepad(); // Loop for handling user input until 'x' is pressed.
  void nextPage(); // Move to the next page
  void prevPage(); // Move to the previous page
  void updateLocationDescription();
  static void clear();

  const std::vector<std::vector<std::string>>& getPages() const {
      return pages;
  }

  int getCurrentPage() const {
      return currentPage;
  }
  void addNoteAutomatically(const std::string& noteContent);

 private:
     friend class NotepadTest;

      std::vector<std::vector<std::string>> pages;
       // Each page is a vector of notes (strings)::vector<std::string> pages;
       // stores the notes
      int currentPage; // Current page being viewed
};

#endif  // NOTEPAD_H_INCLUDED

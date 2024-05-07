/**
 * @file: Notepad.cpp
 * @author: Justin P, Miller F
 * @date: 2024-03-23, 2024-03-25
 */

/**
 * To use this class you must write (for example):
 * Notepad myNotepad;
 * myNotepad.runNotepad();
 */
#include "Notepad.h"

#include <iostream>
#include <limits>

Notepad::Notepad() : currentPage(0) {
  setLocationDescription(
      "You have entered the Notepad Window.\n"
      "Notepad - a: Add note, d: Display notes, e: Edit note, "
      "n: Add page, x: Exit\n"
      "Choose an option:");
  // Start with a single empty page
  pages.push_back(std::vector<std::string>());
}

Notepad::Notepad(std::string n, std::string d) : currentPage(1) {
  locationName = n;
  d = d + std::string("\nCurrent Page: ") + std::
      to_string(currentPage) +std::string("\n"
      "Notepad - a: Add note, d: Display notes, e: Edit note, "
      "n: Add page, p: Previous page, f: Next Page\n"
      "x: Exit\n"
      "Choose an option:");
  setLocationDescription(d);
  setLocationAssociations(nullptr, nullptr,
  nullptr, nullptr);
  // Start with a single empty page
  pages.push_back(std::vector<std::string>());
}

Notepad::Notepad(std::string n) : currentPage(1) {
  locationName = n;
  setLocationDescription("You have entered the Notepad Window.\n");
  //displayNotes();
  // Start with a single empty page
  pages.push_back(std::vector<std::string>());
}

Notepad::~Notepad() {
  for (auto l : locationAssociations) {
    if (l)
      delete l;
  }
}

void Notepad::interact(GameManager* gameManager, std::istream& input) {
  runNotepad(); // Executes from GameManager game loop
}

void Notepad::addNote() {
  clear();

  std::string note;
  std::cout << "Enter your note: ";
  std::getline(std::cin, note);
  pages[currentPage].push_back(note);

  clear();
  std::cout << "Note has been added!\n";
}

void Notepad::displayNotes() const {
  clear();
  for (size_t i = 0; i < pages[currentPage].size(); ++i) {
    std::cout << i + 1 << ": " << pages[currentPage][i] << std::endl;
  }
}

void Notepad::editNote() {
  clear();
  displayNotes();
  std::cout << "Enter line number to edit: ";
  int line;
  std::cin >> line;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n');  // Clear the input buffer
  if (line > 0 && line <= static_cast<int>(pages[currentPage].size())) {
    std::cout << "Enter new note: ";
    std::string newNote;
    std::getline(std::cin, newNote);
    pages[currentPage][line - 1] =
        newNote;  // Replace the old note with the new one
  } else {
    std::cout << "Invalid line number." << std::endl;
  }
  clear();
}

void Notepad::addPage() {
    clear();
    size_t previousSize = pages.size();
    pages.push_back(std::vector<std::string>());
    currentPage = pages.size() - 1;  // Move to the new page;
    if (previousSize < pages.size()) {
        std::cout << "Added a new page." << std::endl;
        std::cout << "Moved from page " << currentPage << " to page " <<
            currentPage + 1 << "." << std::endl;
    } else {
        std::cout << "Failed to add a new page." << std::endl;
    }
    updateLocationDescription();
}

void Notepad::nextPage() {
  clear();
  if (currentPage < pages.size() - 1) {
    currentPage++;
    std::cout << "Moved to next page." << std::endl;
  } else {
    std::cout << "This is the last page." << std::endl;
  }
  updateLocationDescription();
}

void Notepad::prevPage() {
    clear();
    if (currentPage > 0) {
        currentPage--;
        std::cout << "Moved to previous page." << std::endl;
        displayNotes(); // Display notes of the new current page
    } else {
        std::cout << "This is the first page." << std::endl;
    }
    updateLocationDescription();
}

void Notepad::runNotepad() {
  char choice;
  do {
    std::cout << getLocationDescription();
    // Instructions should be provided on how to use this program here
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                    '\n');  // Clear the newline character after the choice

    switch (choice) {
      case 'a':
        addNote();
        break;
      case 'd':
        displayNotes();
        break;
      case 'e':
        editNote();
        break;
      case 'n':
        addPage();
        break;
      case 'p':
        prevPage();
        break;
      case 'f':
        nextPage();
        break;
    }
  } while (choice != 'x');
}

// ANSI escape code to clear the console of previous input
void Notepad::clear() { std::cout << "\x1B[2J\x1B[H"; }

void Notepad::updateLocationDescription() {
    std::string description = "You have entered the Notepad Window.\n";
    description += "Current Page: " + std::to_string(currentPage + 1) + "\n";
    description += "Notepad - a: Add note, d: Display notes, e: Edit note, "
        "n: Add page, p: Previous page, f: Next Page\n"
        "x: Exit\n"
        "Choose an option:";
    setLocationDescription(description);
}

void Notepad::addNoteAutomatically(const std::string& noteContent) {
    pages[currentPage].push_back(noteContent);
}

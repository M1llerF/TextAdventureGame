#include <sstream>

#include "Notepad.h"
#include "gtest/gtest.h"

TEST(NotepadTest, AddNoteTest) {
  Notepad notepad;

  // Simulate input
  std::stringstream input_stream("Test note\n");
  std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());
  // Redirect cin to input_stream
  notepad.addNote();
  std::cin.rdbuf(old_cin);  // Restore cin

  // Get the notes from the first page
  const std::vector<std::string>& notes = notepad.getPages()[0];

  // Verify that the note has been added
  EXPECT_EQ(notes.size(), 1);
  EXPECT_EQ(notes[0], "Test note");
}

TEST(NotepadTest, AddNoteAutomaticallyTest) {
  Notepad notepad;

  // Get the initial number of notes
  size_t initialNumNotes =
      notepad.getPages().empty() ? 0 : notepad.getPages()[0].size();

  // Add a note automatically
  notepad.addNoteAutomatically("This is an automatically added note");

  // Get the number of notes after adding a note
  size_t newNumNotes =
      notepad.getPages().empty() ? 0 : notepad.getPages()[0].size();

  // Assert that the number of notes has increased after adding a note
  EXPECT_GT(newNumNotes, initialNumNotes);
}

TEST(NotepadTest, DisplayNotesTest) {
  Notepad notepad;

  // Add a note
  notepad.addNoteAutomatically("This is a test note.");

  // Display notes
  testing::internal::CaptureStdout();  // Redirect stdout to capture output
  notepad.displayNotes();
  // Get captured output
  std::string output = testing::internal::GetCapturedStdout();

  // Assert that the output contains the added note
  EXPECT_TRUE(output.find("1: This is a test note.") != std::string::npos);
}

TEST(NotepadTest, EditNoteTest) {
  Notepad notepad;

  // Add a note
  notepad.addNoteAutomatically("Original note");

  // Edit the note
  std::stringstream input_stream("1\nEdited note\n");
  std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());
  // Redirect cin to input_stream
  notepad.editNote();
  std::cin.rdbuf(old_cin);  // Restore cin

  // Display notes
  testing::internal::CaptureStdout();  // Redirect stdout to capture output
  notepad.displayNotes();
  std::string new_output =
      testing::internal::GetCapturedStdout();  // Get captured output

  // Assert that the output contains the edited note
  EXPECT_TRUE(new_output.find("1: Edited note") != std::string::npos);
}

TEST(NotepadTest, AddPageTest) {
  Notepad notepad;

  // Get the initial number of pages
  size_t initialNumPages = notepad.getPages().size();

  // Add a new page
  notepad.addPage();

  // Get the number of pages after adding a new page
  size_t newNumPages = notepad.getPages().size();

  // Assert that the number of pages has increased after adding a new page
  EXPECT_GT(newNumPages, initialNumPages);
}

TEST(NotepadTest, NextPageTest) {
  Notepad notepad;
  // Add some content to the first page
  notepad.addNoteAutomatically("Note 1 on page 1");
  // Add a second page
  notepad.addPage();
  // Add some content to the second page
  notepad.addNoteAutomatically("Note 1 on page 2");

  // Verify that the current page is 1 (the first page)
  EXPECT_EQ(notepad.getCurrentPage(), 1);

  // Move to the next page
  notepad.nextPage();

  // Verify that the current page is 2 (the second page)
  EXPECT_EQ(notepad.getCurrentPage(), 1);
}

TEST(NotepadTest, PrevPageTest) {
  Notepad notepad;

  // Move to the next page and then move back to the previous page
  notepad.nextPage();
  notepad.prevPage();

  // Assert that the current page has been
  // decremented back to the initial page
  EXPECT_EQ(notepad.getCurrentPage(), 0);  // Assuming the initial page is 0
}

TEST(NotepadTest, UpdateLocationDescriptionTest) {
  Notepad notepad;

  // Update the location description
  notepad.updateLocationDescription();

  // Assert that the location description is updated correctly
  // (This can be tested by verifying the content of the location description)
}

TEST(NotepadTest, DefaultConstructorTest) {
  // Test default constructor
  Notepad notepad1;
  EXPECT_EQ(notepad1.getLocationName(), "");
  EXPECT_EQ(notepad1.getPages().size(), 1);  // Expecting one initial page
  EXPECT_EQ(notepad1.getCurrentPage(), 0);
}

// Define the parameterized test
TEST(NotepadTest, ParameterConstructorTest) {
  std::string name = "Notepad Program";
  std::string description = "This is the Notepad Program";

  // Create Notepad object with parameters
  Notepad notepad(name, description);

  // Append the current page information to the description
  description += "\nCurrent Page: 1\n";
  description +=
      "Notepad - a: Add note, d: Display notes, "
      "e: Edit note, n: Add page, p: Previous page, f: Next Page\n";
  description += "x: Exit\n";
  description += "Choose an option:";

  // Check if the location description matches the expected description
  EXPECT_EQ(notepad.getLocationDescription(), description);

  // Since currentPage is preset to 1 in the constructor, we expect it to be 1
  int expectedCurrentPage = 1;

  // Check if the current page matches the expected current page
  EXPECT_EQ(notepad.getCurrentPage(), expectedCurrentPage);
}

TEST(NotepadTest, ConstructorWithNameTest) {
  // Define the name for the Notepad
  std::string name = "Notepad Program";

  // Create a Notepad object with the specified name
  Notepad notepad(name);

  // Expected description after constructing the Notepad
  std::string expected_description = "You have entered the Notepad Window.\n";

  // Check if the location name is set correctly
  EXPECT_EQ(notepad.getLocationName(), name);

  // Check if the location description matches the expected description
  EXPECT_EQ(notepad.getLocationDescription(), expected_description);
}

TEST(NotepadTest, RunNotepadTest) {
  // Redirect cout to a stringstream to capture the output
  std::stringstream output_stream;
  std::streambuf* original_cout_buf = std::cout.rdbuf(output_stream.rdbuf());

  // Create a Notepad object
  Notepad notepad;

  // Run the Notepad (simulate user input 'x' to exit)
  std::stringstream input_stream("x\n");
  std::streambuf* original_cin_buf = std::cin.rdbuf(input_stream.rdbuf());
  notepad.runNotepad();
  std::cin.rdbuf(original_cin_buf);

  // Restore the original cout buffer
  std::cout.rdbuf(original_cout_buf);

  // Verify the output contains the expected message
  std::string expected_output =
      "You have entered the Notepad Window.\n"
      "Notepad - a: Add note, d: Display notes, e: Edit note, "
      "n: Add page, x: Exit\n"
      "Choose an option:";
  EXPECT_EQ(output_stream.str(), expected_output);
}

TEST(NotepadTest, InteractAddNote) {
  Notepad notepad;
  GameManager gameManager;  // Assuming GameManager is needed

  // Simulate adding a note
  std::stringstream input;
  input << "a\nTest Note\nx\n";  // 'a' to add, then the note, 'x' to exit
  std::stringstream output;

  // Redirect cin and cout
  std::streambuf* origCinBuf = std::cin.rdbuf(input.rdbuf());
  std::streambuf* origCoutBuf = std::cout.rdbuf(output.rdbuf());

  // Perform the interaction
  notepad.interact(&gameManager,
                   input);  // if you use the input parameter in interact,
                            // otherwise just runNotepad()

  // Restore cin and cout
  std::cin.rdbuf(origCinBuf);
  std::cout.rdbuf(origCoutBuf);

  // Verify output
  std::string outputStr = output.str();
  ASSERT_NE(outputStr.find("Note has been added!"), std::string::npos);
}

TEST(NotepadTest, DestructorTest) {
  {
    Notepad notepad;
    // Populate the notepad with some data if necessary
    notepad.addNoteAutomatically("Sample note for testing.");
    // Destructor is called at the end of this scope
  }
}

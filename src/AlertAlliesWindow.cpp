#include "AlertAlliesWindow.h"

AlertAlliesWindow::AlertAlliesWindow(std::string n, std::string d) {
  locationName = n;
  setLocationDescription(d);
  setLocationAssociations(nullptr, nullptr, nullptr, nullptr);
}

AlertAlliesWindow::~AlertAlliesWindow() {
  for (auto l : locationAssociations) {
    delete l;
  }
}

void AlertAlliesWindow::interact(GameManager* gameManager,
std::istream& input) {
  std::string chosenAlerts;
  std::cout << getLocationDescription() << std::endl;
  input >> chosenAlerts;
  if (chosenAlerts == "back") {
    gameManager->handleBackCommand();
    return;
  }
  if (chosenAlerts == "15" || chosenAlerts == "51") {
    std::cout << "You have alerted the allies correctly!" << std::endl;
    std::cout << "The allies have been alerted and are on their way to \n"
                 "rescue you and the other prisoners. You have \n"
                 "successfully completed the mission!\n"
              << std::endl;
    gameManager->getWinFlag()->setValue(true);

  } else {
    std::cout << "You have alerted the allies incorrectly!" << std::endl;
    std::cout << "Later that night the ground was stained with \n"
                 "the blood of your allies. Many mothers have \n"
                 "lost their children because of your wrong orders.\n"
              << std::endl;
    gameManager->getLoseFlag()->setValue(true);
  }
}

void AlertAlliesWindow::setLocationAssociations(Location* up, Location* down,
                                                Location* left,
                                                Location* right) {}

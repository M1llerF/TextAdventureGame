#ifndef ALERTALLIESWINDOW_H_INCLUDED
#define ALERTALLIESWINDOW_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "Location.h"
#include "GameManager.h"
#include "Event.h"

class AlertAlliesWindow : public Location {
 private:
  std::vector<std::string> alerts; // To store list of alerts
  GameManager* gameManager;
 public:
  AlertAlliesWindow();
  AlertAlliesWindow(std::string, std::string description);
  virtual ~AlertAlliesWindow();
  // Overidden interact method
  void interact(GameManager* gameManager, std::istream& input) override;
  // Implement the listAlerts method
  void listAlerts();
  // Implement the sendAlert method
  void sendAlert(const std::string& alertType);
  void setLocationAssociations(
  Location*, Location*, Location*, Location*) override;
};

#endif // ALERTALLIESWINDOW_H_INCLUDED

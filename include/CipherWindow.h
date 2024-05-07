/**
 * @file: CipherWindow.h
 * @author: Justin P
 * @date: 2024-03-23
 */

#ifndef CIPHERWINDOW_H_INCLUDED
#define CIPHERWINDOW_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>

#include "Location.h"
#include "Event.h"
#include "GameManager.h"

class CipherWindow : public Location {
 public:
  CipherWindow();
  CipherWindow(std::string name, std::string description);
  void interact(GameManager* gameManager, std::istream& input) override;
  ~CipherWindow();
  void setLocationAssociations(
    Location*, Location*, Location*, Location*) override;
  void listCiphers();
 private:
  // Add other methods
};

#endif // CIPHERWINDOW_H_INCLUDED


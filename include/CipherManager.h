#ifndef CIPHERMANAGER_H
#define CIPHERMANAGER_H

#include <string>
#include <vector>

#include "Cipher.h"

class CipherManager {
 private:
  std::vector<Cipher> ciphers;  // Stores all ciphers

 public:
  CipherManager();
  ~CipherManager();
  void updateOriginalText(int index, const std::string& newText);
  void initializeCiphers();
  void addCipher(const Cipher& cipher);

  void markAsTranslated(int index, const std::string& translatedText);
  void markAsCompleted(int index, const std::string& completedText);
  // New method to mark ciphers as completed

  const std::vector<Cipher>& getAllCiphers() const { return ciphers; }
  std::vector<Cipher> getUntranslatedCiphers() const;
  std::vector<Cipher> getTranslatedCiphers() const;
  std::vector<Cipher> getCompletedCiphers() const;
  // Method to get completed ciphers
};

#endif  // CIPHERMANAGER_H

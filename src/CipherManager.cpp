#include "CipherManager.h"

#include <iostream>
CipherManager::CipherManager() { initializeCiphers(); }

void CipherManager::addCipher(const Cipher& cipher) {
  ciphers.push_back(cipher);
}

void CipherManager::initializeCiphers() {
  /**
    "Cipher 3 Original",
    "Cipher 3 Unranslated",
      "Cipher 3 Translated",
      "Cipher 3 SOLUTION"
  */
  ciphers.push_back(
      Cipher("Die 1. Infanteriedivision bewegt sich in Richtung "
             "West-Verdantburg. Voraussichtliche Ankunft in 48 Stunden.",

             "Die 1. Infanteriedivision bewegt sich in Richtung "
             "West-Verdantburg. Voraussichtliche Ankunft in 48 Stunden.",

             "1st Infantry Division moving towards West Verdantburg. Estimated "
             "arrival in 48 hours. ",

             "1st Infantry Division moving towards West Verdantburg. Estimated "
             "arrival in 48 hours. "));
  ciphers.push_back(
      Cipher("kkw kk", "Not applicable", "Not applicable", "Shift 41"));

  // Shift 41
  ciphers.push_back(
      Cipher("Otp 1. Tyqlyepctpotgtdtzy rcptqe ylns Plde Gpcolymfcr.",

             "Die 1. Infanteriedivision greift nach East Verdanburg.",

             "1st Infantry Division feinting to East Verdanburg.",

             "Something about moving to East Verdanburg."));

  ciphers.push_back(
      Cipher("... -.-. .... .. -.-. .... - / -. . ..- -. --.. . .... -. / . .. "
             "-. ..- -. -.. ...- .. . .-. --.. .. --.",  // Original text
             "SCHICHT NEUNZEHN EINUNDVIERZIG",           // Untranslated
             "Shift next: 1945",                         // Translated
             "Shift next: 1945. Wonder what that could mean."));  // Solution

  // Shift 1945
  ciphers.push_back(
      Cipher("Iwnsljsij Fsbjnxzsl ijx Tgjwptrrfsitx: Kzmwjs Xnj ijs Fslwnkk "
             "zsfgmfslnl atr bniwnljs Bjyyjw ns Tufqxyjfi izwhm. "
             "Jwktqlxpwnynxhm. Inj Ywzuujs rüxxjs atwbfwyx iwfsljs.",
             "Dringende Anweisung des Oberkommandos: Fuhren Sie den Angriff "
             "unabhangig vom widrigen Wetter in Opalstead durch. "
             "Erfolgskritisch. Die Truppen müssen vorwarts drangen.",
             "Urgent Instructions from High Command: Conduct the attack "
             "regardless of the adverse weather in Opalstead. Critical to "
             "success. The troops must press forward.",
             "Something about attacking Opalstead regardless of weather..."));

  ciphers.push_back(Cipher(
      "..-. .-. .. . -. -.. .-.. -.-- / -.-. .- ..- - .. --- -. / .. -. - . "
      ".-. -.-. . .--. - . -.. / -- . ... ... .- --. . / ..-. --- ..- .-. / .. "
      "... / .--. .- .-. - / --- ..-. / . -. . -- -.-- / -- .. ... .. -. ..-. "
      "--- .-. -- .- - .. --- -. / -.-. .- -- .--. .- .. --. -. / -... . .-.. "
      ".. . ...- . / - .... . / --- .--. .--. --- ... .. - .",
      "Not applicable", "Not applicable",
      "Friendly. Caution: Intercepted messages part of enemy "
      "misinformation campaign. BELIEVE THE OPPOSITE"));
}

// Add more ciphers as needed

CipherManager::~CipherManager() {
  // No dynamic memory to clean up
}

void CipherManager::updateOriginalText(int index, const std::string& newText) {
  if (index >= 0 && index < ciphers.size()) {
    ciphers[index].originalText = newText;
    std::cout << "Cipher " << index << " original text updated successfully.\n";
  } else {
    std::cout << "Invalid index for updating cipher text.\n";
  }
}

void CipherManager::markAsTranslated(int index,
                                     const std::string& translatedText) {
  if (index >= 0 && index < ciphers.size()) {
    ciphers[index].translatedText = translatedText;
    ciphers[index].completedText =
        translatedText;  // Assuming completion upon translation
  }
}

std::vector<Cipher> CipherManager::getUntranslatedCiphers() const {
  std::vector<Cipher> untranslated;
  for (const auto& cipher : ciphers) {
    if (cipher.translatedText.empty()) {
      untranslated.push_back(cipher);
    }
  }
  return untranslated;
}

std::vector<Cipher> CipherManager::getTranslatedCiphers() const {
  std::vector<Cipher> translated;
  for (const auto& cipher : ciphers) {
    if (!cipher.translatedText.empty()) {
      translated.push_back(cipher);
    }
  }
  return translated;
}

void CipherManager::markAsCompleted(int index,
                                    const std::string& completedText) {
  if (index >= 0 && index < ciphers.size()) {
    ciphers[index].completedText =
        completedText;  // Mark the cipher as completed
  }
}

std::vector<Cipher> CipherManager::getCompletedCiphers() const {
  std::vector<Cipher> completed;
  for (const auto& cipher : ciphers) {
    if (!cipher.completedText.empty()) {
      completed.push_back(cipher);
    }
  }
  return completed;
}

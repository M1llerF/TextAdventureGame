#ifndef CIPHER_H
#define CIPHER_H

#include <string>

class Cipher {
 public:
  std::string originalText;
  std::string untranslatedText;  // Updated to hold the untranslated cipher text
  std::string translatedText;
  std::string completedText;  // Updated to hold the completed cipher text

  Cipher(const std::string& original, const std::string& untranslated = "",
         const std::string& translated = "", const std::string& completed = "")
      : originalText(original),
        untranslatedText(untranslated),
        translatedText(translated),
        completedText(completed) {}
};

#endif  // CIPHER_H

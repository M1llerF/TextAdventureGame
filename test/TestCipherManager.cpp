/**
 * @file: TestCipherManager.cpp
 * @author: Justin P
 * @date: 2024-04-04
 */

#include "gtest/gtest.h"
#include "CipherManager.h"
#include "Cipher.h"

TEST(TestCipherManager, testCipherManager) {
  CipherManager cipherManager;
  Cipher cipher("Original", "", "");
  cipherManager.addCipher(cipher);
  EXPECT_GT(cipherManager.getUntranslatedCiphers().size(), 0);
  cipherManager.markAsTranslated(0, "Translated");
  EXPECT_GT(cipherManager.getTranslatedCiphers().size(), 0);
  cipherManager.markAsCompleted(0, "Completed");
  EXPECT_GT(cipherManager.getCompletedCiphers().size(), 0);
}

#pragma once

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

inline bool AreCharsEqual(const char &ch1, const char &ch2) {
  return std::tolower(static_cast<unsigned char>(ch1)) ==
         std::tolower(static_cast<unsigned char>(ch2));
}

inline bool AreStringsEqual(const std::string &str1, const std::string &str2) {
  return std::equal(str1.begin(), str1.end(), str2.begin(), str2.end(),
                    AreCharsEqual);
}

inline void ClearScreen() { std::cout << "\033[2J\033[1;1H"; }
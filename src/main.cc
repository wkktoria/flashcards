#include "db.h"
#include "flashcard.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

void ShowUsage() {
  std::cout << "\nAvailable commands:\n\t- add - add a new flashcard\n\t- show "
               "- show all "
               "flashcards\n\t- quit - quit the program";
}

bool AreCharsEqual(const char &ch1, const char &ch2) {
  return std::tolower(static_cast<unsigned char>(ch1)) ==
         std::tolower(static_cast<unsigned char>(ch2));
}

bool AreStringsEqual(const std::string &str1, const std::string &str2) {
  return std::equal(str1.begin(), str1.end(), str2.begin(), str2.end(),
                    AreCharsEqual);
}

int main() {
  Db db{};
  bool is_running{true};

  ShowUsage();
  while (is_running) {
    std::cout << "\n\n> ";
    std::string command{};
    std::getline(std::cin >> std::ws, command);

    if (AreStringsEqual(command, "add")) {
      std::cout << "front: ";
      std::string front{};
      std::getline(std::cin >> std::ws, front);

      std::cout << "back: ";
      std::string back{};
      std::getline(std::cin >> std::ws, back);

      Flashcard flashcard(front, back);

      db.Add(flashcard);
    } else if (AreStringsEqual(command, "show")) {
      db.Show();
    } else if (AreStringsEqual(command, "quit")) {
      is_running = false;
    } else {
      std::cout << "Invalid command!\n";
    }
  }

  return 0;
}
#include "session.h"
#include "db.h"
#include "flashcard.h"
#include "helpers.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <string>

Session::Session() { flashcards_ = db_.GetAll(); }

void Session::Start() {
  auto now{std::chrono::system_clock::now()};
  std::time_t current_time{std::chrono::system_clock::to_time_t(now)};
  std::cout << "Session started at: " << std::ctime(&current_time) << '\n';

  ShowUsage();

  while (!quit_) {

    std::cout << "\n\n> ";
    std::string command{};
    std::getline(std::cin >> std::ws, command);

    if (AreStringsEqual(command, "study")) {
      ClearScreen();
      Study();
    } else if (AreStringsEqual(command, "add")) {
      ClearScreen();

      std::cout << "(add) front: ";
      std::string front{};
      std::getline(std::cin >> std::ws, front);

      std::cout << "(add) back: ";
      std::string back{};
      std::getline(std::cin >> std::ws, back);

      Flashcard flashcard(front, back);
      db_.Add(flashcard);
    } else if (AreStringsEqual(command, "show")) {
      ClearScreen();
      db_.Show();
    } else if (AreStringsEqual(command, "help")) {
      ClearScreen();
      ShowUsage();
    } else if (AreStringsEqual(command, "quit")) {
      quit_ = true;
    } else {
      std::cout << "Invalid command!\n";
    }
  }

  now = std::chrono::system_clock::now();
  current_time = std::chrono::system_clock::to_time_t(now);
  std::cout << "Session finished at: " << std::ctime(&current_time) << '\n';
}

void Session::Study() {
  if (flashcards_.empty()) {
    std::cout << "No flashcard added. Add some and try again!\n";
    return;
  }

  auto start{std::chrono::steady_clock::now()};
  auto size{static_cast<unsigned int>(flashcards_.size() - 1)};

  std::random_device dev{};
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, size);

  std::cout << "Study session started. To quit study session type 'qs'.\n";
  std::cout << "Press anything to start study...\n";
  std::cin.get();

  while (true) {
    ClearScreen();

    auto flashcard{flashcards_.at(dist(rng))};
    flashcard.Show(ToShow::kFront);

    std::cout << "(study) back: ";
    std::string back{};
    std::getline(std::cin >> std::ws, back);

    if (AreStringsEqual(back, "qs")) {
      ClearScreen();
      std::cout << "Study time: "
                << std::chrono::duration_cast<std::chrono::seconds>(
                       std::chrono::steady_clock::now() - start)
                       .count()
                << "seconds\n";
      break;
    }

    if (AreStringsEqual(back, flashcard.back())) {
      std::cout << "Correct!\n";
    } else {
      std::cout << "Wrong! Correct answer is: " << flashcard.back() << '\n';
    }

    std::cout << "Press anything to continue...\n";
    std::cin.get();
  }
}

void Session::ShowUsage() {
  std::cout << "Available commands:\n\t- study - study flashcards\n\t- add - "
               "add a new flashcard\n\t- show "
               "- show all "
               "flashcards\n\t- help - show available commands\n\t- quit - "
               "quit the program\n\n";
}
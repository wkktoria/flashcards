#pragma once

#include "db.h"
#include "flashcard.h"
#include <vector>

class Session {
public:
  Session();
  ~Session() = default;

  void Start();
  void Study();

private:
  void ShowUsage();

  Db db_{};
  std::vector<Flashcard> flashcards_{};
  bool quit_{false};
};
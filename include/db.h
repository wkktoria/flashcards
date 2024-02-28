#pragma once

#include "flashcard.h"
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>

class Db {
public:
  Db();
  ~Db() = default;

  void Add(const Flashcard &flashcard);
  void Show();
  std::vector<Flashcard> GetAll();

private:
  bool IsEmpty();

  SQLite::Database db_;
};
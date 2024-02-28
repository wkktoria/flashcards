#pragma once

#include "flashcard.h"
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/SQLiteCpp.h>

class Db {
public:
  Db();
  ~Db() = default;

  void Add(const Flashcard &flashcard);
  void Show();

private:
  bool IsEmpty();

  SQLite::Database db_;
};
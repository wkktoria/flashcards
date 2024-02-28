#include "db.h"
#include "flashcard.h"
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>
#include <exception>
#include <iostream>
#include <vector>

Db::Db()
    : db_(SQLite::Database("./flashcards.db",
                           SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)) {
  db_.exec("CREATE TABLE IF NOT EXISTS flashcards(id INTEGER PRIMARY KEY "
           "AUTOINCREMENT, front TEXT, back TEXT)");
}

void Db::Add(const Flashcard &flashcard) {
  try {
    SQLite::Statement query(
        db_, "INSERT INTO flashcards(front, back) VALUES(:front, :back)");

    query.bind(":front", flashcard.front());
    query.bind(":back", flashcard.back());

    query.exec();

    std::cout << "Flashcard has been added.\n";
  } catch (std::exception &e) {
    std::cout << "Flashcard has NOT been added.\n";
  }
}

void Db::Show() {
  if (IsEmpty()) {
    std::cout << "No flashcards added!\n";
    return;
  }

  try {
    SQLite::Statement query(db_, "SELECT front, back FROM flashcards");

    while (query.executeStep()) {
      Flashcard flashcard(query.getColumn("front").getString(),
                          query.getColumn("back").getString());

      flashcard.Show(ToShow::kFull);
    }
  } catch (std::exception &e) {
    std::cout << e.what() << '\n';
  }
}

bool Db::IsEmpty() {
  int size{};

  try {
    SQLite::Statement query(db_, "SELECT COUNT(*) as size FROM flashcards");

    while (query.executeStep()) {
      size = query.getColumn("size").getInt();
    }
  } catch (std::exception &e) {
    std::cout << e.what() << '\n';
  }

  return size == 0;
}

std::vector<Flashcard> Db::GetAll() {
  std::vector<Flashcard> flashcards{};

  try {
    SQLite::Statement query(db_, "SELECT front, back FROM flashcards");

    while (query.executeStep()) {
      Flashcard flashcard(query.getColumn("front").getString(),
                          query.getColumn("back").getString());

      flashcards.push_back(flashcard);
    }
  } catch (std::exception &e) {
    std::cout << e.what() << '\n';
  }

  return flashcards;
}
#pragma once

#include <string>

enum class ToShow { kFull, kFront, kBack };

class Flashcard {
public:
  Flashcard() = default;
  Flashcard(const std::string &front, const std::string &back);
  ~Flashcard() = default;

  std::string front() const;
  std::string back() const;

  void Show(ToShow to_show) const;

private:
  std::string front_{};
  std::string back_{};
};
#include "flashcard.h"
#include <iostream>
#include <string>

Flashcard::Flashcard(const std::string &front, const std::string &back)
    : front_(front), back_(back) {}

std::string Flashcard::front() const { return front_; }

std::string Flashcard::back() const { return back_; }

void Flashcard::Show(ToShow to_show) const {
  switch (to_show) {
  case ToShow::kFull:
    std::cout << "FRONT: " << front_ << "\tBACK: " << back_ << '\n';
    break;
  case ToShow::kFront:
    std::cout << "FRONT: " << front_ << '\n';
    break;
  case ToShow::kBack:
    std::cout << "\tBACK: " << back_ << '\n';
    break;
  }
}
#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include "shiftand.hpp"


ShiftAnd::ShiftAnd(const std::string &P, const std::string &T) 
  : P_(P), T_(T), accept_(0ULL), chars_(SIGMA) {
}


ShiftAnd::~ShiftAnd() {
}


void ShiftAnd::preprocess() {
  std::size_t m = P_.size();
  accept_ = 1ULL << m-1;
  for (char ch = 0; ch < chars_.size(); ++ch)
    chars_[ch] = 0ULL;
  for (std::size_t j = 0; j < m; ++j)
    chars_[P_[j]] |= 1ULL << j;
}


ssize_t ShiftAnd::search() const {
  std::size_t m = P_.size();
  std::size_t n = T_.size();
  uint64_t state_ = 0ULL;
  for (std::size_t i = 0; i < n; ++i) {
    state_ = ((state_ << 1) | 1ULL) & chars_[T_[i]];

    if ((state_& accept_) != 0ULL)
      return i-m+1;

  }
  return -1;
}

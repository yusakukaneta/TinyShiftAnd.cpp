#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include "xshiftand.hpp"


XShiftAnd::XShiftAnd(const std::string &P, const std::string &T)
  : P_(P), T_(T), chars_(SIGMA), repeats_(SIGMA) {
}


XShiftAnd::~XShiftAnd() {
}


void XShiftAnd::preprocess() {
  std::size_t m = P_.size();
  std::size_t n = T_.size();
  std::size_t l = 0; // The number of normal characters in P
  epsblk_ = 0ULL;
  for (char ch = 0; ch < chars_.size(); ++ch) {
    chars_[ch] = 0ULL;
    repeats_[ch] = 0ULL;
  }
  int i = -1;
  char lastch = P_[0];
  for (std::size_t j = 0; j < m; ++j) {

    if (P_[j] == '+') {
      repeats_[lastch] |= 1ULL << i;
    }
    else if (P_[j] == '?') {
      epsblk_ |= 1ULL << i;
    }
    else if (P_[j] == '*') {
      repeats_[lastch] |= 1ULL << i;
      epsblk_ |= 1ULL << i;
    }
    else {
      lastch = P_[j];
      ++l;
      ++i;
      chars_[lastch] |= 1ULL << i;
    }
  }

  accept_ = 1ULL << l-1;
  epsbeg_ = 0ULL;
  epsend_ = 0ULL;
  for (std::size_t i = 0; i < l; ++i) {

    if ((epsblk_ & (1ULL << i)) != 0ULL) {
      if ((epsend_ & (1ULL << i-1)) == 0ULL)  {
        epsbeg_ |= 1ULL << i-1;
        epsend_ |= 1ULL << i;
      }
      else {
        epsend_ &= ~(1ULL << i-1);
        epsend_ |= 1ULL << i;
      }
    }

  }
}


ssize_t XShiftAnd::search() const {
  std::size_t m = P_.size();
  std::size_t n = T_.size();
  uint64_t state_ = 0ULL;
  uint64_t temp_ = 0ULL;
  for (std::size_t i = 0; i < n; ++i) {
    state_ = (((state_ << 1) | 1) & chars_[T_[i]]) | (state_ & repeats_[T_[i]]);
    temp_ = state_ | epsend_;
    state_ |= epsblk_ & ((~(temp_ - epsbeg_)) ^ temp_);
    if ((state_ & accept_) != 0)
      return i; // Note that this code reports end positions
  }
  return -1;
}

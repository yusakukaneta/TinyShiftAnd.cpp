#ifndef SHIFTAND_HPP
#define SHIFTAND_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>

// Shift-And algorithm by Baeza-Yates and Gonnet
class ShiftAnd {
  static const std::size_t SIGMA = (1 << 8);

public: 
  ShiftAnd(const std::string &P, const std::string &T);
  ~ShiftAnd();

  void preprocess();
  ssize_t search() const;

private: 
  const std::string P_;
  const std::string T_;
  uint64_t accept_;
  std::vector<uint64_t> chars_;
};

#endif

#ifndef XSHIFTAND_HPP
#define XSHIFTAND_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>

// Extended Shift-And algorithm by Navarro and Raffinot
class XShiftAnd {
  static const std::size_t SIGMA = (1 << 8);

public: 
  XShiftAnd(const std::string &P, const std::string &T);
  ~XShiftAnd();

  void preprocess();
  ssize_t search() const;

private:
  const std::string P_;
  const std::string T_;
  uint64_t accept_;
  uint64_t epsbeg_;
  uint64_t epsend_;
  uint64_t epsblk_;
  std::vector<uint64_t> chars_;
  std::vector<uint64_t> repeats_;
};

#endif

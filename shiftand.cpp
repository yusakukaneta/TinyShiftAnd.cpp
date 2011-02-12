#include <iostream>
#include <string>
#include <vector>

static const std::size_t ALPHA_SIZE = (1 << 8);
typedef unsigned long long int block_t;

// Shift-And Algorithm
class ShiftAnd {
public: 
  ShiftAnd(const std::string &pat, const std::string &txt)
  : P(pat), M(pat.size()), T(txt), N(txt.size()), mskCHR(ALPHA_SIZE)
  {}
  ~ShiftAnd()
  {}
  // Preprocessing
  void preprocess()
  {
    // Build bitmask F
    mskF = 1 << M-1;
    // Build bitmask CHR
    for (std::size_t c = 0; c < mskCHR.size(); ++c)
      mskCHR[c] = 0;
    for (std::size_t j = 0; j < M; ++j)
      mskCHR[P[j]] |= 1 << j;
  }
  // Searching
  int search()
  {
    block_t mskS = 0;
    for (std::size_t i = 0; i < N; ++i) {
      mskS = ((mskS << 1) | 1) & mskCHR[T[i]];
      if ((mskS & mskF) != 0)
        return i-M+1;
    }
    return -1;
  }
private: 
  const std::string P;
  const std::size_t M;
  const std::string T;
  const std::size_t N;
  block_t mskF;
  std::vector<block_t> mskCHR;
};

int main(int argc, char *argv[]) 
{
  if (argc != 3) {
    std::cerr << "The number of arguments is invalid.\n" 
              << "Usage: " << argv[0] << " Pattern Text\n";
    return -1;
  }
  const std::string P(argv[1]);
  const std::string T(argv[2]);
  ShiftAnd PM(P, T);
  PM.preprocess();
  std::cout << PM.search() << std::endl;
}

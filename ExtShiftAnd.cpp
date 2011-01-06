#include <iostream>
#include <string>
#include <vector>

static const std::size_t ALPHA_SIZE = (1 << 8);
typedef unsigned long long int block_t;

// Extended Shift-And Algorithm
class ExtShiftAnd {
public: 
  ExtShiftAnd(const std::string &pat, const std::string &txt)
  : P(pat), M(pat.size()), T(txt), N(txt.size()), mskCHR(ALPHA_SIZE), mskREP(ALPHA_SIZE)
  {}
  ~ExtShiftAnd()
  {}
  // Preprocessing
  void preprocess()
  {
    std::size_t L = 0; // The number of normal characters in P
    // Build bitmasks mskCHR, mskREP, and mskEpsB
    mskEpsB = 0;
    for (std::size_t c = 0; c < mskCHR.size(); ++c) {
      mskCHR[c] = 0;
      mskREP[c] = 0;
    }
    int i = -1;
    char lastc = P[0];
    for (std::size_t j = 0; j < M; ++j) {
      if (P[j] == '+') {
        mskREP[lastc] |= 1 << i;
      }
      else if (P[j] == '?') {
        mskEpsB |= 1 << i;
      }
      else if (P[j] == '*') {
        mskREP[lastc] |= 1 << i;
        mskEpsB |= 1 << i;
      }
      else {
        lastc = P[j];
        ++L;
        ++i;
        mskCHR[lastc] |= 1 << i;
      }
    }
    // Build bitmasks mskF, mskEpsI, and mskEpsF
    mskF = 1 << L-1;
    mskEpsI = 0;
    mskEpsF = 0;
    for (std::size_t i = 0; i < L; ++i) {
      if ((mskEpsB & (1 << i)) != 0) {
        if ((mskEpsF & (1 << i-1)) == 0)  {
          mskEpsI |= 1 << i-1;
          mskEpsF |= 1 << i;
        }
        else {
          mskEpsF &= ~(1 << i-1);
          mskEpsF |= 1 << i;
        }
      }
    }
  }
  // Searching
  int search()
  {
    block_t mskS = 0;
    block_t mskT = 0;
    for (std::size_t i = 0; i < N; ++i) {
      mskS = (((mskS << 1) | 1) & mskCHR[T[i]]) | (mskS & mskREP[T[i]]);
      mskT = mskS | mskEpsF;
      mskS |= mskEpsB & ((~(mskT - mskEpsI)) ^ mskT);
      if ((mskS & mskF) != 0)
        return i; // Note that this code reports end positions
    }
    return -1;
  }

private: 
  const std::string P;
  const std::size_t M;
  const std::string T;
  const std::size_t N;
  block_t mskF;
  block_t mskEpsI;
  block_t mskEpsF;
  block_t mskEpsB;
  std::vector<block_t> mskCHR;
  std::vector<block_t> mskREP;
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
  ExtShiftAnd PM(P, T);
  PM.preprocess();
  std::cout << PM.search() << std::endl;
}

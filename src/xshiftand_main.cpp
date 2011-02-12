#include <iostream>
#include <string>
#include "xshiftand.hpp"

using namespace std;

int main(int argc, char **argv) {
  if (argc != 3) {
    cerr << "The number of arguments is invalid.\n" 
              << "Usage: " << argv[0] << " Pattern Text\n";
    return -1;
  }
  string P(argv[1]);
  string T(argv[2]);
  XShiftAnd s(P, T);
  s.preprocess();
  cout << s.search() << endl;
  return 0;
}

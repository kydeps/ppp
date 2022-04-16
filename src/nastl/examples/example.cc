#pragma ide diagnostic ignored "performance-for-range-copy"

#include <ky/nastl/nastl.h>

using namespace ky::nastl;

int main() {
  auto filename =
      "/Users/kamen/work/ppp/src/nastl/examples/"
      "comma-separated-values-file-1.csv";

  for (auto line : file(filename)) {
    auto terms = line->strip("\n")->split(",");
    print(terms);
  }

  return 0;
}

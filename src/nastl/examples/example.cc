#pragma ide diagnostic ignored "performance-for-range-copy"

#include <ky/nastl/nastl.h>

using namespace ky::nastl;

int main() {
  //  auto f = file("comma-separated-values-file-1.csv");
  auto f = file(
      "/Users/kamen/work/ppp/src/nastl/examples/"
      "comma-separated-values-file-1.csv");

  for (auto line : f) {
    auto terms = string(string(line).strip("\n")).split(",");
    print(terms);
  }

  return 0;
}

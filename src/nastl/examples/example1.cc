#pragma ide diagnostic ignored "performance-for-range-copy"

#include <ky/nastl/nastl.h>

using namespace ky::nastl;

int main() {
  auto f = file("comma-separated-values-file-1.csv");

  for (auto line : f) {
    print(line);
  }

  return 0;
}

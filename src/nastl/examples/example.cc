#pragma ide diagnostic ignored "performance-for-range-copy"

#include <ky/nastl/nastl.h>

using namespace ky::nastl;

int main() {
  auto filename =
      "/Users/kamen/work/ppp/src/nastl/examples/"
      "comma-separated-values-file-1.csv";

  // results = []
  auto results = list();
  // with open(filename) as f:
  //  for line in f:
  //    ...
  for (auto line : file(filename)) {
    // terms = line.strip('\n').split(',')
    auto terms = line->strip("\n")->split(",");
    results.append(terms);
  }
  // results[10:] = []
  results.slice(10) = list();
  // for result in results:
  any r = results;
  for (auto result : r) {
    print(result);
  }

  return 0;
}

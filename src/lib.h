#pragma once

#include <any>
#include <memory>
#include <vector>

using var = std::any;

class List {
public:
  // API -----------------------------------------------------------------------

  void append(var x);

  // Internals -----------------------------------------------------------------

  List(std::initializer_list<var> l);

  using iterator = std::vector<var>::iterator;
  iterator begin();
  iterator end();

  struct Impl;
  std::shared_ptr<Impl> impl_;
};

List list();
List list(std::initializer_list<var> l);

void print(var x);

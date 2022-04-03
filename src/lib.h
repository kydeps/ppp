#pragma once

#include <any>
#include <memory>
#include <optional>

using var = std::any;

class list;

class list_slice {
public:
  void operator=(list &l); // FIXME: this should accept `iterable` instead...
  
  operator var();

  struct Impl;
  std::unique_ptr<Impl> impl_;

  ~list_slice();

private:
  friend class list;

  list_slice(list &l, int from_index, int to_index);
};

class list {
public:
  // API -----------------------------------------------------------------------

  list();
  list(std::initializer_list<var> l);
  list(list_slice &l);

  void append(var x);

  var &operator[](int index);

  list_slice operator()(
      std::optional<int> from_index,
      std::optional<int> to_index);

  // Internals -----------------------------------------------------------------

  var *begin();
  var *end();

  struct Impl;
  std::shared_ptr<Impl> impl_;
};

void print(var x);

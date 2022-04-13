#include "visitor.h"

#include <ky/nastl/exception.h>

namespace ky::nastl {

void visitor::visit() {
  throw not_implemented("visit()");
}

void visitor::visit(integer) {
  throw not_implemented("visit(integer)");
}

void visitor::visit(const list &) {
  throw not_implemented("visit(list)");
}

void visitor::visit(const string &) {
  throw not_implemented("visit(string)");
}

void visitor::visit(const file &) {
  throw not_implemented("visit(file)");
}

}  // namespace ky::nastl
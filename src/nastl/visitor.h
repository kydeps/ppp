#ifndef PPP_SRC_NASTL_VISITOR_H
#define PPP_SRC_NASTL_VISITOR_H

#include <ky/nastl/any.h>

namespace ky::nastl {

class list;
class string;

class visitor {
public:
  virtual void visit() = 0;
  virtual void visit(integer v) = 0;
  virtual void visit(const list &v) = 0;
  virtual void visit(const string &v) = 0;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_VISITOR_H

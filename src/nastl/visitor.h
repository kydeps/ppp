#ifndef PPP_SRC_NASTL_VISITOR_H
#define PPP_SRC_NASTL_VISITOR_H

#include <ky/nastl/any.h>

namespace ky::nastl {

class visitor {
public:
  virtual void visit();
  virtual void visit(integer v);
  virtual void visit(const list &v);
  virtual void visit(const string &v);
  virtual void visit(const file &v);
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_VISITOR_H

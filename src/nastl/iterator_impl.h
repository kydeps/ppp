#ifndef PPP_SRC_NASTL_ITERATOR_IMPL_H
#define PPP_SRC_NASTL_ITERATOR_IMPL_H

namespace ky::nastl {

class iterator::impl {
public:
  virtual ~impl() = default;
  virtual bool equals(const iterator::impl& other) = 0;
  virtual iterator::impl& increment() = 0;
  virtual any &dereference() = 0;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_ITERATOR_IMPL_H

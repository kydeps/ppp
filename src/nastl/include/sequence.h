#ifndef PPP_SRC_NASTL_INCLUDE_SEQUENCE_H
#define PPP_SRC_NASTL_INCLUDE_SEQUENCE_H

#include <ky/nastl/iterable.h>
#include <ky/nastl/types.h>

namespace ky::nastl {

class sequence;

class slice_ final {
public:
  // NOLINTNEXTLINE(misc-unconventional-assign-operator)
  void operator=(const sequence &);

  slice_() = delete;
  slice_(const slice_ &) = delete;
  slice_(slice_ &&) = delete;

private:
  friend class sequence;
  slice_(sequence &, integer bIndex, integer eIndex);

  sequence &values_;
  integer bIndex_;
  integer eIndex_;
};

class sequence : public iterable {
public:
  virtual any &operator[](const integer &) = 0;

  slice_ slice(const any &bIndex, const any &eIndex);
  slice_ slice(const any &);

  [[nodiscard]] virtual integer size() const = 0;

protected:
  [[nodiscard]] integer check_index(const any &index, bool allow_end) const;

  friend class slice_;
  virtual void replace(integer bIndex, integer eIndex, const sequence &) = 0;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_SEQUENCE_H

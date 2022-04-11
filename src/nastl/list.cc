#include <ky/nastl/list.h>

#include "iterator_impl.h"
#include "visitor.h"

namespace ky::nastl {

class list_iterator final : public iterator::impl {
public:
  list_iterator(std::vector<any>::iterator &&iterator)
      : iterator_(std::move(iterator)) {}

  ~list_iterator() override = default;

  bool equals(const iterator::impl &other) override {
    auto o = dynamic_cast<const list_iterator &>(other);
    return iterator_ == o.iterator_;
  }

  iterator::impl &increment() override {
    ++iterator_;
    return *this;
  }

  any &dereference() override { return *iterator_; }

private:
  std::vector<any>::iterator iterator_;
};

list::list() = default;

list::list(const list &) = default;

list::list(std::initializer_list<any> values)
    : values_(std::make_shared<std::vector<any>>(values)) {}

list::~list() = default;

iterator list::begin() const {
  return {std::make_unique<list_iterator>(values_->begin())};
}

iterator list::end() const {
  return {std::make_unique<list_iterator>(values_->end())};
}

integer list::size() const {
  return values_->size();  // NOLINT(cppcoreguidelines-narrowing-conversions)
}

any &list::operator[](const integer &index) { return values_->at(index); }

void list::accept(visitor &v) const { v.visit(*this); }

std::unique_ptr<object> list::clone() const {
  return std::make_unique<list>(*this);
}

bool list::equals(const object &other) const {
  const auto &o = dynamic_cast<const list &>(other);
  return *values_ == *o.values_;
}

}  // namespace ky::nastl
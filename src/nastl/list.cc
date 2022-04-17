#include <ky/nastl/list.h>

#include "iterator_impl.h"
#include "visitor.h"

namespace ky::nastl {

class list_iterator final : public iterator::impl {
public:
  explicit list_iterator(std::vector<any>::iterator &&iterator)
      : iterator_(iterator) {}

  ~list_iterator() override = default;

  bool equals(const iterator::impl &other) override {
    auto o = dynamic_cast<const list_iterator &>(other);
    return iterator_ == o.iterator_;
  }

  iterator::impl &increment() override {
    ++iterator_;
    return *this;
  }

  std::unique_ptr<iterator::impl> add(integer delta) override {
    return std::make_unique<list_iterator>(iterator_ + delta);
  }

  any &dereference() override { return *iterator_; }

private:
  std::vector<any>::iterator iterator_;
};

list::list() : values_(std::make_shared<std::vector<any>>()) {}

list::list(const list &) = default;

list::list(std::initializer_list<any> values)
    : values_(std::make_shared<std::vector<any>>(values)) {}

list::~list() = default;

void list::append(const any &v) { slice(size()) = list({v}); }

void list::extend(const any &v) {
  slice(size()) = v.as_object();
}

void list::insert(const any &index, const any &value) {
  slice(index, index) = list({value});
}

void list::clear() { slice(0) = list(); }

any list::copy() const {
  auto result = list();
  result.extend(*this);
  return result;
}

void list::reverse() { std::reverse(values_->begin(), values_->end()); }

any list::count(const any &value) const {
  return std::count(begin(), end(), value);
}

any list::index(const any &value, const any &bIndex, const any &eIndex) const {
  auto b = values_->begin() + check_index(bIndex, true);
  auto e = values_->begin() + check_index(eIndex, true);
  auto c = std::find(b, e, value);
  if (c == e) {
    throw value_error();
  }
  return c - b;
}

void list::remove(const any &value) {
  auto i = index(value);
  slice(i, i + 1) = list();
}

any list::pop(const any &index) {
  auto i = check_index(index, false);
  auto result = (*this)[i];
  slice(i, i + 1) = list();
  return result;
}

void list::sort(const std::function<any(any)> &key, bool reverse) {
  auto compare = [key, reverse](const any &x, const any &y) {
    return (key(x) < key(y)) != reverse;
  };
  std::sort(values_->begin(), values_->end(), compare);
}

iterator list::begin() const {
  return {std::make_unique<list_iterator>(values_->begin())};
}

iterator list::end() const {
  return {std::make_unique<list_iterator>(values_->end())};
}

integer list::size() const {
  return values_->size();  // NOLINT(cppcoreguidelines-narrowing-conversions)
}

any &list::operator[](const integer &index) const {
  return values_->at(check_index(index, false));
}

void list::accept(visitor &v) const { v.visit(*this); }

bool list::equals(const object &other) const {
  const auto &o = dynamic_cast<const list &>(other);
  return *values_ == *o.values_;
}

bool list::less(const object &other) const {
  const auto &o = dynamic_cast<const list &>(other);
  return std::lexicographical_compare(
      values_->begin(),
      values_->end(),
      o.values_->begin(),
      o.values_->end());
}

std::unique_ptr<object> list::clone() const {
  return std::make_unique<list>(*this);
}

void list::replace(integer bIndex, integer eIndex, const sequence &s) {
  auto &dst = *values_;
  auto dst_b = dst.begin() + check_index(bIndex, true);
  auto dst_e = dst.begin() + check_index(eIndex, true);
  integer dst_s = dst_e - dst_b;

  auto src_b = s.begin();
  auto src_e = s.end();
  integer src_s = s.size();

  if (dst_s < src_s) {
    std::copy(src_b, src_b + dst_s, dst_b);
    dst.insert(dst_e, src_b + dst_s, src_e);
  } else {
    std::copy(src_b, src_e, dst_b);
    dst.erase(dst_b + src_s, dst_e);
  }
}

}  // namespace ky::nastl
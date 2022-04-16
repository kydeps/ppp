#include <ky/nastl/string.h>

#include "iterator_impl.h"

namespace ky::nastl {

namespace {

class string_iterator final : public iterator::impl {
public:
  explicit string_iterator(std::string::iterator &&iterator) : iterator_(iterator) {}

  ~string_iterator() override = default;

  bool equals(const iterator::impl &other) override {
    auto o = dynamic_cast<const string_iterator &>(other);
    return iterator_ == o.iterator_;
  }

  iterator::impl &increment() override {
    ++iterator_;
    return *this;
  }

  std::unique_ptr<iterator::impl> add(integer delta) override {
    return std::make_unique<string_iterator>(iterator_ + delta);
  }

  any &dereference() override { throw std::runtime_error("not implemented"); }

private:
  std::string::iterator iterator_;
};

}  // namespace

iterator string::begin() const {
  return {std::make_unique<string_iterator>(value_->begin())};
}

iterator string::end() const {
  return {std::make_unique<string_iterator>(value_->end())};
}

}  // namespace ky::nastl
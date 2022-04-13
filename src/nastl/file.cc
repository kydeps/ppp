#include "include/file.h"

#include <ky/nastl/file.h>

#include "impl.h"
#include "iterator_impl.h"
#include "visitor.h"

namespace ky::nastl {

file::file(const any &filename) : file(filename, "r") {}

file::file(const any &filename, const any &mode)
    : file_(fopen(impl::get_c_str(filename), impl::get_c_str(mode))) {
  if (file_ == nullptr) {
    auto s = strerror(errno);
    throw io_error(s);
  }
}

file::~file() {
  // TODO: check for error?
  fclose(file_);
}

void file::accept(visitor &v) const { v.visit(*this); }

class file_iterator final : public iterator::impl {
public:
  explicit file_iterator(FILE *file, bool end) : file_(file), end_(end) {
    increment();
  };

  bool equals(const iterator::impl &other) override {
    return end_ == dynamic_cast<const file_iterator &>(other).end_;
  }

  iterator::impl &increment() override {
    std::string result;
    char buffer[1024];

    while (true) {
      fgets(buffer, sizeof(buffer), file_);
      if (feof(file_)) {
        end_ = true;
        break;
      }
      if (ferror(file_)) {
        throw io_error("error reading file");
      }
      result += buffer;
      if (result[result.size() - 1] == '\n') {
        break;
      }
    }

    current_line_ = result;

    return *this;
  }

  std::unique_ptr<iterator::impl> add(integer delta) override {
    throw not_implemented("add");
  }

  any &dereference() override {
    // TODO
    //  1. this should not be mutable
    //  2. this should brobably fail if end_ is true
    return current_line_;
  }

private:
  FILE *file_;
  any current_line_;
  bool end_;
};

iterator file::begin() const {
  return {std::make_unique<file_iterator>(file_, false)};
}

iterator file::end() const {
  return {std::make_unique<file_iterator>(file_, true)};
}

}  // namespace ky::nastl

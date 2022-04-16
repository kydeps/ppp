#include <ky/nastl/any.h>
#include <ky/nastl/list.h>
#include <ky/nastl/string.h>

#include <limits>

#include "to_std_string.h"

namespace ky::nastl {

any string::split(const any &sep, const any &max_splits) const {
  auto separator = to_std_string(sep);
  auto splits = max_splits.get<integer>();

  auto value = *value_;
  integer position = 0;

  list result;

  while (splits > 0) {
    auto new_position = value.find(separator, position);
    if (new_position == std::string::npos) {
      result.append(value.substr(position));
      return result;
    }

    result.append(value.substr(position, new_position - position));
    position = static_cast<integer>(new_position + separator.size());
    --splits;
  }

  result.append(value.substr(position));
  return result;
}

any string::split(const any &sep) const {
  return split(sep, std::numeric_limits<integer>::max());
}

any string::strip(const any &chars) const {
  auto c = to_std_string(chars);

  auto value = *value_;

  auto fIndex = value.find_first_not_of(c);
  auto eIndex = value.find_last_not_of(c);

  if (eIndex == std::string::npos) {
    return value.substr(fIndex);
  } else {
    return value.substr(fIndex, eIndex - fIndex + 1);
  }
}

any string::strip() const { return strip("\n\t "); }

}  // namespace ky::nastl

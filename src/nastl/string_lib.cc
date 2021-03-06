#include <ky/nastl/any.h>
#include <ky/nastl/list.h>
#include <ky/nastl/string.h>

#include <limits>

#include "to_std_string.h"
#include "impl.h"

namespace ky::nastl {

any string::split(const any &sep, const any &max_splits) const {
  auto separator = *sep.as_object<string>().value_;
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

any string::strip(const any &chars) const {
  auto c = *chars.as_object<string>().value_;;

  auto value = *value_;

  auto fIndex = value.find_first_not_of(c);
  auto eIndex = value.find_last_not_of(c);

  if (eIndex == std::string::npos) {
    return value.substr(fIndex);
  } else {
    return value.substr(fIndex, eIndex - fIndex + 1);
  }
}

}  // namespace ky::nastl

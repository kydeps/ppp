#pragma once

#include <ppp/var.h>

namespace ppp {

bool operator==(const var &x, const var &y);

bool operator<(const var &x, const var &y);

}  // namespace ppp
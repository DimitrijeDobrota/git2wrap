#include <string>

#include "git2wrap/git2wrap.hpp"

auto main() -> int
{
  auto const exported = exported_class {};

  return std::string("git2wrap") == exported.name() ? 0 : 1;
}

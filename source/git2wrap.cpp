#include <string>

#include "git2wrap/git2wrap.hpp"

exported_class::exported_class()
    : m_name {"git2wrap"}
{
}

auto exported_class::name() const -> char const*
{
  return m_name.c_str();
}

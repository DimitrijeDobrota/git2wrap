#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT oid
{
public:
  explicit oid(const git_oid* objid);

  operator bool() const { return m_oid != nullptr; }  // NOLINT
  git_oid* ptr() const { return m_oid.get(); }

  std::string get_hex_string(size_t n);

private:
  oidPtr m_oid;
};

}  // namespace git2wrap

#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT reference
{
public:
  explicit reference(git_reference* ref = nullptr);

  operator bool() const { return m_ref != nullptr; }  // NOLINT
  [[nodiscard]] reference dup() const;

  [[nodiscard]] git_reference* get() const { return m_ref.get(); }

  friend bool operator==(const reference& lhs, const reference& rhs);
  friend bool operator!=(const reference& lhs, const reference& rhs);

private:
  referenceUPtr m_ref;
};

}  // namespace git2wrap

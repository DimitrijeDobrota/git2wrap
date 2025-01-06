#pragma once

#include <functional>
#include <memory>

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT reference
{
public:
  explicit reference(git_reference* ref = nullptr);
  explicit operator bool() const { return m_ref != nullptr; }

  git_reference* get() { return m_ref.get(); }
  const git_reference* get() const { return m_ref.get(); }

  friend bool operator==(const reference& lhs, const reference& rhs);
  friend bool operator!=(const reference& lhs, const reference& rhs);

private:
  using delete_f = std::function<void(git_reference*)>;
  std::unique_ptr<git_reference, delete_f> m_ref;
};

}  // namespace git2wrap

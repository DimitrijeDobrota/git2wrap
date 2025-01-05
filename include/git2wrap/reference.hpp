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

  git_reference* get() const;

private:
  std::unique_ptr<git_reference, std::function<void(git_reference*)>> m_ref;
};

}  // namespace git2wrap

#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT libgit2
{
public:
  libgit2();
  ~libgit2();

  libgit2(const libgit2&) = delete;
  libgit2(libgit2&&) = delete;
  libgit2& operator=(const libgit2&) = delete;
  libgit2& operator=(libgit2&&) = delete;

private:
  int m_cinit = 0;
};

}  // namespace git2wrap

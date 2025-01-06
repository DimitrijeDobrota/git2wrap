#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT buf
{
public:
  buf() = default;
  buf(const buf&) = default;
  buf(buf&&) = default;
  buf& operator=(const buf&) = default;
  buf& operator=(buf&&) = default;
  ~buf();

  git_buf* get() { return &m_buf; }
  const git_buf* get() const { return &m_buf; }

private:
  git_buf m_buf = {nullptr, 0, 0};
};

}  // namespace git2wrap

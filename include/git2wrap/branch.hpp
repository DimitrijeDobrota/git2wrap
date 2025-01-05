#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/reference.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT branch
{
public:
  explicit branch(git_reference* ref = nullptr,
                  git_branch_t type = git_branch_t(0));

  git_branch_t get_type() const { return m_type; }
  git_reference* get_reference() const { return m_ref.get(); }

  const std::string& get_name();

private:
  reference m_ref;
  git_branch_t m_type = {};

  std::string m_name;
};

}  // namespace git2wrap

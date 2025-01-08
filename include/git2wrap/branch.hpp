#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT branch
{
public:
  explicit branch(git_reference* ref = nullptr,
                  git_branch_t type = git_branch_t(0));
  explicit branch(referencePtr ref, git_branch_t type = git_branch_t(0));

  operator bool() const { return m_ref != nullptr; }  // NOLINT
  git_branch_t get_type() const { return m_type; }

  const std::string& get_name();

private:
  referenceUPtr m_ref;
  git_branch_t m_type = {};

  std::string m_name;
};

class branch_iterator
{
public:
  explicit branch_iterator(git_branch_iterator* iter = nullptr);

  git_branch_iterator* get() { return m_iter.get(); }
  const git_branch_iterator* get() const { return m_iter.get(); }

  branch& operator*() { return m_branch; }
  branch* operator->() { return &m_branch; }
  branch_iterator& operator++();

  friend bool operator==(const branch_iterator& lhs,
                         const branch_iterator& rhs);

  friend bool operator!=(const branch_iterator& lhs,
                         const branch_iterator& rhs);

private:
  branch_iteratorUPtr m_iter;
  branch m_branch;
};

}  // namespace git2wrap

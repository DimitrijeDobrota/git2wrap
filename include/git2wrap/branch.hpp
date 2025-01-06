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

  git_reference* get_reference() { return m_ref.get(); }
  const git_reference* get_reference() const { return m_ref.get(); }

  const std::string& get_name();

private:
  reference m_ref;
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
  using delete_f = std::function<void(git_branch_iterator*)>;
  std::unique_ptr<git_branch_iterator, delete_f> m_iter;
  branch m_branch;
};

}  // namespace git2wrap

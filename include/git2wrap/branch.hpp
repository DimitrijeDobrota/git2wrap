#pragma once

#include <based/enum/enum_flag.hpp>
#include <based/types/types.hpp>
#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/reference.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT branch
{
public:
  explicit branch(
      git_reference* ref = nullptr, git_branch_t type = git_branch_t(0)
  );
  branch(reference ref, git_branch_t type);

  BASED_DECLARE_ENUM_FLAG(flags_list, based::u8, local, remote, all)

  operator bool() const { return m_ref; }  // NOLINT
  [[nodiscard]] branch dup() const;

  [[nodiscard]] git_branch_t get_type() const { return m_type; }

  const std::string& get_name();

private:
  reference m_ref;
  git_branch_t m_type;

  std::string m_name;
};

BASED_DEFINE_ENUM_FLAG_CLASS(branch, flags_list, based::u8, local, remote, all)

class branch_iterator
{
public:
  explicit branch_iterator(git_branch_iterator* iter = nullptr);

  [[nodiscard]] git_branch_iterator* get() { return m_iter.get(); }
  [[nodiscard]] const git_branch_iterator* get() const { return m_iter.get(); }

  branch& operator*() { return m_branch; }
  branch* operator->() { return &m_branch; }
  branch_iterator& operator++();

  friend bool operator==(
      const branch_iterator& lhs, const branch_iterator& rhs
  );

  friend bool operator!=(
      const branch_iterator& lhs, const branch_iterator& rhs
  );

private:
  branch_iteratorUPtr m_iter;
  branch m_branch;
};

}  // namespace git2wrap

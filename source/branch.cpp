#include "git2wrap/branch.hpp"

#include "git2wrap/error.hpp"

namespace git2wrap
{
branch::branch(git_reference* ref, git_branch_t type)
    : m_ref(ref, git_reference_free)
    , m_type(type)
{
}

const std::string& branch::get_name()
{
  if (!m_name.empty()) {
    return m_name;
  }

  const char* name = nullptr;
  if (auto err = git_branch_name(&name, m_ref.get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return m_name = name;
}

branch_iterator::branch_iterator(git_branch_iterator* iter)
    : m_iter(iter, git_branch_iterator_free)
{
  if (iter != nullptr) {
    ++*this;
  }
}

branch_iterator& branch_iterator::operator++()
{
  git_reference* ref = nullptr;
  git_branch_t type = {};

  if (auto err = git_branch_next(&ref, &type, get())) {
    if (err != GIT_ITEROVER) {
      throw error(err, git_error_last(), __FILE__, __LINE__);
    }
  }

  m_branch = branch(ref, type);
  return *this;
}

bool operator==(const branch_iterator& lhs, const branch_iterator& rhs)
{
  return lhs.m_branch.get_reference() == rhs.m_branch.get_reference();
}

bool operator!=(const branch_iterator& lhs, const branch_iterator& rhs)
{
  return !(lhs == rhs);
}

}  // namespace git2wrap

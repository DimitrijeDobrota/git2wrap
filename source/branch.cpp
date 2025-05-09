#include "git2wrap/branch.hpp"

#include "git2wrap/error.hpp"

namespace git2wrap
{

branch::branch(git_reference* ref, git_branch_t type)
    : m_ref(ref)
    , m_type(type)
{
}

branch::branch(reference ref, git_branch_t type)
    : m_ref(std::move(ref))
    , m_type(type)
{
}

branch branch::dup() const
{
  return {m_ref.dup(), m_type};
}

const std::string& branch::get_name()
{
  if (!m_name.empty()) {
    return m_name;
  }

  const char* name = nullptr;
  const auto err = error_code_t(git_branch_name(&name, m_ref.get()));

  if (err == error_code_t::ok) {
    return m_name = name;
  }

  if (err == error_code_t::einvalid) {
    throw error<error_code_t::einvalid>();
  }

  throw error<error_code_t::error>();
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

  const auto err = error_code_t(git_branch_next(&ref, &type, get()));
  if (err == error_code_t::ok || err == error_code_t::iterover) {
    m_branch = branch(ref, type);
    return *this;
  }

  throw error<error_code_t::error>();
}

bool operator==(const branch_iterator& lhs, const branch_iterator& rhs)
{
  return lhs.m_branch == rhs.m_branch;
}

bool operator!=(const branch_iterator& lhs, const branch_iterator& rhs)
{
  return !(lhs == rhs);
}

}  // namespace git2wrap

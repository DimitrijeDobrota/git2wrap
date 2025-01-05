#include "git2wrap/git2wrap.hpp"

namespace git2wrap
{

branch::branch(git_reference* ref, git_branch_t type)
    : m_ref(ref)
    , m_type(type)
{
}

branch::branch(branch&& rhs) noexcept
{
  std::swap(m_ref, rhs.m_ref);
  std::swap(m_type, rhs.m_type);
  std::swap(m_name, rhs.m_name);
}

branch& branch::operator=(branch&& rhs) noexcept
{
  std::swap(m_ref, rhs.m_ref);
  std::swap(m_type, rhs.m_type);
  std::swap(m_name, rhs.m_name);

  return *this;
}

branch::~branch()
{
  git_reference_free(m_ref);
  m_ref = nullptr;
}

const std::string& branch::get_name()
{
  if (!m_name.empty()) {
    return m_name;
  }

  const char* name = nullptr;
  if (auto err = git_branch_name(&name, m_ref)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return m_name = name;
}

}  // namespace git2wrap

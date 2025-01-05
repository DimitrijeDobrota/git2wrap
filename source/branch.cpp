#include "git2wrap/branch.hpp"

#include "git2wrap/error.hpp"

namespace git2wrap
{

branch::branch(git_reference* ref, git_branch_t type)
    : m_ref(ref)
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

}  // namespace git2wrap

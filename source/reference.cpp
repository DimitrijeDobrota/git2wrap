#include "git2wrap/reference.hpp"

namespace git2wrap
{

reference::reference(git_reference* ref)
    : m_ref(ref, git_reference_free)
{
}

reference reference::dup() const
{
  git_reference* ref = nullptr;
  git_reference_dup(&ref, m_ref.get());
  return reference(ref);
}

bool operator==(const reference& lhs, const reference& rhs)
{
  return git_reference_cmp(lhs.m_ref.get(), rhs.m_ref.get()) == 0;
}

bool operator!=(const reference& lhs, const reference& rhs)
{
  return !(lhs == rhs);
}

}  // namespace git2wrap

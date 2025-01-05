#include "git2wrap/reference.hpp"

namespace git2wrap
{

reference::reference(git_reference* ref)
    : m_ref(ref, git_reference_free)
{
}

git_reference* reference::get() const
{
  return m_ref.get();
}

}  // namespace git2wrap

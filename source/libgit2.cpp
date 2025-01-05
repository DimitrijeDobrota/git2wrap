#include "git2wrap/git2wrap.hpp"

namespace git2wrap
{

libgit2::libgit2()
{
  if (m_cinit = git_libgit2_init(); m_cinit < 0) {
    throw error(m_cinit, git_error_last(), __FILE__, __LINE__);
  }
}

libgit2::~libgit2()
{
  git_libgit2_shutdown();
}

}  // namespace git2wrap

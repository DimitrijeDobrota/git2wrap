#include "git2wrap/libgit2.hpp"

#include "git2wrap/error.hpp"

namespace git2wrap
{

libgit2::libgit2()
{
  if (m_cinit = git_libgit2_init(); m_cinit < 0) {
    throw error<error_code_t::ERROR>();
  }
}

libgit2::~libgit2()
{
  git_libgit2_shutdown();
}

}  // namespace git2wrap

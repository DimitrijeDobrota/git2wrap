#include "git2wrap/commit.hpp"

#include "git2wrap/error.hpp"

namespace git2wrap
{

commit::commit(git_commit* commit, repository& repo)
    : m_commit(commit, git_commit_free)
    , m_repo(&repo)
{
}

const git_oid* commit::get_id() const
{
  return git_commit_id(get());
}

const char* commit::get_summary() const
{
  return git_commit_summary(get());
}

}  // namespace git2wrap

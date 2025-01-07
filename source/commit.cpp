#include "git2wrap/commit.hpp"

namespace git2wrap
{

commit::commit(git_commit* cmt, repositoryPtr repo)
    : m_commit(cmt, git_commit_free)
    , m_repo(std::move(repo))
{
}

const git_oid* commit::get_id() const
{
  return git_commit_id(m_commit.get());
}

const char* commit::get_summary() const
{
  return git_commit_summary(m_commit.get());
}

}  // namespace git2wrap

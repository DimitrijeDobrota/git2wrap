#include "git2wrap/revwalk.hpp"

#include "git2wrap/error.hpp"
#include "git2wrap/repository.hpp"

namespace git2wrap
{

revwalk::revwalk(repositoryPtr repo)
    : m_repo(std::move(repo))
{
  git_revwalk* rwalk = nullptr;

  if (auto err = git_revwalk_new(&rwalk, m_repo.get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  m_revwalk = {rwalk, git_revwalk_free};
}

void revwalk::push(const git_oid* objid)
{
  if (auto err = git_revwalk_push(m_revwalk.get(), objid)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }
}

void revwalk::push_glob(const char* glob)
{
  if (auto err = git_revwalk_push_glob(m_revwalk.get(), glob)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }
}

void revwalk::push_head()
{
  if (auto err = git_revwalk_push_head(m_revwalk.get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }
}

commit revwalk::next()
{
  static git_oid objid;

  if (git_revwalk_next(&objid, m_revwalk.get()) == 0) {
    return repository(m_repo).commit_lookup(&objid);
  }

  return {};
}

void revwalk::reset()
{
  if (auto err = git_revwalk_reset(m_revwalk.get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }
}

}  // namespace git2wrap

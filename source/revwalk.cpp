#include "git2wrap/revwalk.hpp"

#include "git2wrap/error.hpp"
#include "git2wrap/repository.hpp"

namespace git2wrap
{

revwalk::revwalk(repository& repo)
    : m_repo(&repo)
{
  git_revwalk* rwalk = nullptr;

  if (auto err = git_revwalk_new(&rwalk, repo.get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  m_revwalk = {rwalk, git_revwalk_free};
}

void revwalk::push(const git_oid* oid)
{
  if (auto err = git_revwalk_push(get(), oid)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }
}

void revwalk::push_glob(const char* glob)
{
  if (auto err = git_revwalk_push_glob(get(), glob)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }
}

void revwalk::push_head()
{
  if (auto err = git_revwalk_push_head(get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }
}

commit revwalk::next()
{
  static git_oid oid;

  if (git_revwalk_next(&oid, get()) == 0) {
    return m_repo->commit_lookup(&oid);
  }

  return {};
}

void revwalk::reset()
{
  if (auto err = git_revwalk_reset(get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }
}

}  // namespace git2wrap

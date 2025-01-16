#include "git2wrap/revwalk.hpp"

#include "git2wrap/error.hpp"
#include "git2wrap/repository.hpp"

namespace git2wrap
{

revwalk::revwalk(repositoryPtr repo)
    : m_repo(std::move(repo))
{
  git_revwalk* rwalk = nullptr;

  if (git_revwalk_new(&rwalk, m_repo.get()) != 0) {
    throw error<error_code_t::ERROR>();
  }

  m_revwalk = {rwalk, git_revwalk_free};
}

void revwalk::push(const oid& objid)
{
  if (git_revwalk_push(m_revwalk.get(), objid.ptr()) != 0) {
    throw error<error_code_t::ERROR>();
  }
}

void revwalk::push_glob(const char* glob)
{
  if (git_revwalk_push_glob(m_revwalk.get(), glob) != 0) {
    throw error<error_code_t::ERROR>();
  }
}

void revwalk::push_head()
{
  if (git_revwalk_push_head(m_revwalk.get()) != 0) {
    throw error<error_code_t::ERROR>();
  }
}

commit revwalk::next()
{
  static git_oid objid;

  switch (git_revwalk_next(&objid, m_revwalk.get())) {
    case error_code_t::OK:
      return repository(m_repo).commit_lookup(oid(&objid));
    case error_code_t::ITEROVER:
      break;
  }

  return {};
}

void revwalk::reset()
{
  if (git_revwalk_reset(m_revwalk.get()) != 0) {
    throw error<error_code_t::ERROR>();
  }
}

}  // namespace git2wrap

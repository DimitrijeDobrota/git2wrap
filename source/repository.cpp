#include "git2wrap/repository.hpp"

#include "git2wrap/commit.hpp"
#include "git2wrap/error.hpp"
#include "git2wrap/tag.hpp"

namespace git2wrap
{

repository::repository(git_repository* repo)
    : m_repo(repo, git_repository_free)
{
}

repository::repository(repositoryPtr repo)
    : m_repo(std::move(repo))
{
}

repository::repository(const char* path, unsigned is_bare)
{
  git_repository* repo = nullptr;

  if (git_repository_init(&repo, path, is_bare) != 0) {
    throw error<error_code_t::error>();
  }

  m_repo = {repo, git_repository_free};
}

repository::repository(const char* path, init_options* opts)
{
  git_repository* repo = nullptr;

  if (git_repository_init_ext(&repo, path, opts) != 0) {
    throw error<error_code_t::error>();
  }

  m_repo = {repo, git_repository_free};
}

repository repository::clone(
    const char* url, const char* local_path, const clone_options* options
)
{
  git_repository* repo = nullptr;

  if (git_clone(&repo, url, local_path, options) != 0) {
    throw error<error_code_t::error>();
  }

  return repository(repo);
}

repository repository::open(const char* path)
{
  git_repository* repo = nullptr;

  if (git_repository_open(&repo, path) != 0) {
    throw error<error_code_t::error>();
  }

  return repository(repo);
}

repository repository::open(
    const char* path, flags_open::enum_type flags, const char* ceiling_dirs
)
{
  git_repository* repo = nullptr;

  const auto err = error_code_t(
      git_repository_open_ext(&repo, path, flags.value, ceiling_dirs)
  );

  if (err == error_code_t::ok) {
    return repository(repo);
  }

  if (err == error_code_t::enotfound) {
    throw error<error_code_t::enotfound>();
  }

  throw error<error_code_t::error>();
}

object repository::revparse(const char* spec) const
{
  git_object* obj = nullptr;

  const auto err = error_code_t(git_revparse_single(&obj, m_repo.get(), spec));
  if (err == error_code_t::ok) {
    return {obj, m_repo};
  }

  if (err == error_code_t::enotfound) {
    throw error<error_code_t::enotfound>();
  }

  if (err == error_code_t::eambiguous) {
    throw error<error_code_t::eambiguous>();
  }

  if (err == error_code_t::einvalidspec) {
    throw error<error_code_t::einvalidspec>();
  }

  throw error<error_code_t::error>();
}

commit repository::commit_lookup(const oid& objid) const
{
  git_commit* commit = nullptr;

  if (git_commit_lookup(&commit, m_repo.get(), objid.ptr()) != 0) {
    throw error<error_code_t::error>();
  }

  return {commit, m_repo};
}

blob repository::blob_lookup(const oid& objid) const
{
  git_blob* blob = nullptr;

  if (git_blob_lookup(&blob, m_repo.get(), objid.ptr()) != 0) {
    throw error<error_code_t::error>();
  }

  return {blob, m_repo};
}

tag repository::tag_lookup(const oid& objid) const
{
  git_tag* tagg = nullptr;

  if (git_tag_lookup(&tagg, m_repo.get(), objid.ptr()) != 0) {
    throw error<error_code_t::error>();
  }

  return {tagg, m_repo};
}

branch_iterator repository::branch_end() const  // NOLINT
{
  return branch_iterator();
}

branch_iterator repository::branch_begin(branch::flags_list::enum_type flags
) const
{
  git_branch_iterator* iter = nullptr;

  if (git_branch_iterator_new(&iter, m_repo.get(), git_branch_t(flags.value))
      != 0)
  {
    throw error<error_code_t::error>();
  }

  return branch_iterator(iter);
}

void repository::tag_foreach(git_tag_foreach_cb callback, void* payload) const
{
  if (git_tag_foreach(m_repo.get(), callback, payload) != 0) {
    throw error<error_code_t::error>();
  }
}

}  // namespace git2wrap

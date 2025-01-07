#include "git2wrap/repository.hpp"

#include "git2wrap/error.hpp"

namespace git2wrap
{

repository::repository(git_repository* repo)
    : m_repo(repo, git_repository_free)
{
}

repository::repository(const char* path, unsigned is_bare)
{
  git_repository* repo = nullptr;

  if (auto err = git_repository_init(&repo, path, is_bare)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  m_repo = {repo, git_repository_free};
}

repository::repository(const char* path, init_options* opts)
{
  git_repository* repo = nullptr;

  if (auto err = git_repository_init_ext(&repo, path, opts)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  m_repo = {repo, git_repository_free};
}

repository repository::clone(const char* url,
                             const char* local_path,
                             const clone_options* options)
{
  git_repository* repo = nullptr;

  if (auto err = git_clone(&repo, url, local_path, options)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return repository(repo);
}

repository repository::open(const char* path)
{
  git_repository* repo = nullptr;

  if (auto err = git_repository_open(&repo, path)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return repository(repo);
}

repository repository::open(const char* path,
                            unsigned flags,
                            const char* ceiling_dirs)
{
  git_repository* repo = nullptr;

  if (auto err = git_repository_open_ext(&repo, path, flags, ceiling_dirs)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return repository(repo);
}

object repository::revparse(const char* spec)
{
  git_object* obj = nullptr;

  if (auto err = git_revparse_single(&obj, get(), spec)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return object(obj);
}

commit repository::commit_lookup(const git_oid* oid)
{
  git_commit* commit = nullptr;
  if (auto err = git_commit_lookup(&commit, get(), oid)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return {commit, *this};
}

branch_iterator repository::branch_end() const  // NOLINT
{
  return branch_iterator();
}

branch_iterator repository::branch_begin(git_branch_t list_flags)
{
  git_branch_iterator* iter = nullptr;

  if (auto err = git_branch_iterator_new(&iter, get(), list_flags)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return branch_iterator(iter);
}

}  // namespace git2wrap

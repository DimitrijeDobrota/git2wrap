#include "git2wrap/git2wrap.hpp"

namespace git2wrap
{

repository::repository(git_repository* repo)
    : m_repo(repo)
{
}

repository::repository(const char* path, unsigned is_bare)
{
  if (auto err = git_repository_init(&m_repo, path, is_bare)) {
    throw error(err, git_error_last());
  }
}

repository::repository(const char* path, init_options* opts)
{
  if (auto err = git_repository_init_ext(&m_repo, path, opts)) {
    throw error(err, git_error_last());
  }
}

repository::~repository()
{
  git_repository_free(m_repo);
}

repository repository::clone(const char* url,
                             const char* local_path,
                             const clone_options* options)
{
  git_repository* repo = nullptr;

  if (auto err = git_clone(&repo, url, local_path, options)) {
    throw error(err, git_error_last());
  }

  return repository(repo);
}

repository repository::open(const char* path)
{
  git_repository* repo = nullptr;

  if (auto err = git_repository_open(&repo, path)) {
    throw error(err, git_error_last());
  }

  return repository(repo);
}

repository repository::open(const char* path,
                            unsigned flags,
                            const char* ceiling_dirs)
{
  git_repository* repo = nullptr;

  if (auto err = git_repository_open_ext(&repo, path, flags, ceiling_dirs)) {
    throw error(err, git_error_last());
  }

  return repository(repo);
}

}  // namespace git2wrap

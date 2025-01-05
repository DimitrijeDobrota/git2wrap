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
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }
}

repository::repository(const char* path, init_options* opts)
{
  if (auto err = git_repository_init_ext(&m_repo, path, opts)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }
}

repository::~repository()
{
  git_repository_free(m_repo);
  m_repo = nullptr;
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

repository::branch_iterator::branch_iterator(git_branch_iterator* iter)
    : m_iter(iter)
{
  ++*this;
}

repository::branch_iterator::~branch_iterator()
{
  git_branch_iterator_free(m_iter);
  m_iter = nullptr;
}

repository::branch_iterator& repository::branch_iterator::operator++()
{
  git_reference* ref = nullptr;
  git_branch_t type = {};

  if (auto err = git_branch_next(&ref, &type, m_iter)) {
    if (err != GIT_ITEROVER) {
      throw error(err, git_error_last(), __FILE__, __LINE__);
    }
  }

  m_branch = {ref, type};
  return *this;
}

repository::branch_iterator repository::branch_begin(
    git_branch_t list_flags) const
{
  git_branch_iterator* iter = nullptr;

  if (auto err = git_branch_iterator_new(&iter, m_repo, list_flags)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return branch_iterator(iter);
}

repository::branch_iterator repository::branch_end() const  // NOLINT
{
  return {};
}

bool operator!=(const repository::branch_iterator& lhs,
                const repository::branch_iterator& rhs)
{
  return lhs.m_branch.get_reference() != rhs.m_branch.get_reference();
}

}  // namespace git2wrap

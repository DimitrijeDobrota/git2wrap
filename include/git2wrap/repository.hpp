#pragma once

#include <git2.h>

#include "git2wrap/branch.hpp"
#include "git2wrap/git2wrap_export.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT repository
{
public:
  using init_options = git_repository_init_options;
  using clone_options = git_clone_options;

  explicit repository(git_repository* repo);
  repository(const char* path, unsigned is_bare);
  repository(const char* path, init_options* opts);

  static repository clone(const char* url,
                          const char* local_path,
                          const clone_options* options);

  static repository open(const char* path);
  static repository open(const char* path,
                         unsigned flags,
                         const char* ceiling_dirs);

  struct branch_iterator
  {
    explicit branch_iterator(git_branch_iterator* iter);
    branch_iterator() = default;

    branch_iterator(const branch_iterator&) = delete;
    branch_iterator& operator=(const branch_iterator&) = delete;

    branch_iterator(branch_iterator&&) = default;
    branch_iterator& operator=(branch_iterator&&) = default;

    ~branch_iterator();

    branch& operator*() { return m_branch; }
    branch* operator->() { return &m_branch; }
    branch_iterator& operator++();

    friend bool operator==(const branch_iterator& lhs,
                           const branch_iterator& rhs);

    friend bool operator!=(const branch_iterator& lhs,
                           const branch_iterator& rhs);

  private:
    git_branch_iterator* m_iter = nullptr;
    branch m_branch;
  };

  branch_iterator branch_begin(git_branch_t list_flags) const;
  branch_iterator branch_end() const;

private:
  std::unique_ptr<git_repository, std::function<void(git_repository*)>> m_repo;
};

}  // namespace git2wrap

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

  git_repository* get() { return m_repo.get(); }
  const git_repository* get() const { return m_repo.get(); }

  static repository clone(const char* url,
                          const char* local_path,
                          const clone_options* options);

  static repository open(const char* path);
  static repository open(const char* path,
                         unsigned flags,
                         const char* ceiling_dirs);

  branch_iterator branch_begin(git_branch_t list_flags);
  branch_iterator branch_end() const;

private:
  using delete_f = std::function<void(git_repository*)>;
  std::unique_ptr<git_repository, delete_f> m_repo;
};

}  // namespace git2wrap

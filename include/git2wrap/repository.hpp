#pragma once

#include <based/enum/enum_flag.hpp>
#include <based/types/types.hpp>
#include <git2.h>

#include "git2wrap/blob.hpp"
#include "git2wrap/branch.hpp"
#include "git2wrap/commit.hpp"
#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/object.hpp"
#include "git2wrap/oid.hpp"
#include "git2wrap/tag.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT repository
{
public:
  using init_options = git_repository_init_options;
  using clone_options = git_clone_options;

  BASED_DECLARE_ENUM_FLAG(
      flags_open, based::u8, no_search, cross_fs, bare, no_dotgit, from_env
  )

  explicit repository(git_repository* repo);
  explicit repository(repositoryPtr repo);
  repository(const char* path, unsigned is_bare);
  repository(const char* path, init_options* opts);

  operator repositoryPtr() const { return m_repo; }  // NOLINT
  operator bool() const { return m_repo != nullptr; }  // NOLINT
  [[nodiscard]] repositoryPtr get() const { return m_repo; }

  static repository clone(
      const char* url, const char* local_path, const clone_options* options
  );

  static repository open(const char* path);
  static repository open(
      const char* path, flags_open::type flags, const char* ceiling_dirs
  );

  object revparse(const char* spec) const;
  [[nodiscard]] commit commit_lookup(const oid& objid) const;
  [[nodiscard]] blob blob_lookup(const oid& objid) const;
  [[nodiscard]] tag tag_lookup(const oid& objid) const;

  [[nodiscard]] branch_iterator branch_begin(branch::flags_list::type flags) const;
  [[nodiscard]] branch_iterator branch_end() const;

  void tag_foreach(tag_foreach_cb callback, void* payload) const;

private:
  repositoryPtr m_repo;
};

BASED_DEFINE_ENUM_FLAG_CLASS(
    repository,
    flags_open,
    based::u8,
    no_search,
    cross_fs,
    bare,
    no_dotgit,
    from_env
)

}  // namespace git2wrap

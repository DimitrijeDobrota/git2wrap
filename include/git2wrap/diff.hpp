#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/tree.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT diff
{
public:
  diff(git_diff* dif, repositoryPtr repo);

  operator bool() const { return m_diff != nullptr; }  // NOLINT

  diff_stats get_stats() const;

  int foreach(diff_file_cb file_cb,
              diff_binary_cb binary_cb,
              diff_hunk_cb hunk_cb,
              diff_line_cb line_cb,
              void* payload) const;

  static diff tree_to_tree(const tree& old,
                           const tree& crnt,
                           const git_diff_options* opts);

private:
  diffUPtr m_diff;
  repositoryPtr m_repo;
};

class GIT2WRAP_EXPORT diff_stats
{
public:
  explicit diff_stats(git_diff_stats* stats);

  size_t files_changed() const;
  size_t insertions() const;
  size_t deletions() const;

private:
  diff_statsUPtr m_stats;
};

}  // namespace git2wrap

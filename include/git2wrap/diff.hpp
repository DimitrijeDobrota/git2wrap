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

}  // namespace git2wrap

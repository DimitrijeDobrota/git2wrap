#include "git2wrap/diff.hpp"

#include "git2wrap/error.hpp"

namespace git2wrap
{

diff::diff(git_diff* dif, repositoryPtr repo)
    : m_diff(dif, git_diff_free)
    , m_repo(std::move(repo))
{
}

int diff::foreach(diff_file_cb file_cb,
                  diff_binary_cb binary_cb,
                  diff_hunk_cb hunk_cb,
                  diff_line_cb line_cb,
                  void* payload) const
{
  return git_diff_foreach(
      m_diff.get(), file_cb, binary_cb, hunk_cb, line_cb, payload);
}

diff diff::tree_to_tree(const tree& old,
                        const tree& crnt,
                        const git_diff_options* opts)
{
  git_diff* dif = nullptr;

  if (auto err = git_diff_tree_to_tree(
          &dif, old.get_owner().get(), old.ptr(), crnt.ptr(), opts))
  {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return {dif, old.get_owner()};
}

}  // namespace git2wrap

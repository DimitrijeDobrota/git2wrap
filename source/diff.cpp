#include "git2wrap/diff.hpp"

#include "git2wrap/error.hpp"

namespace git2wrap
{

diff::diff(git_diff* dif, repositoryPtr repo)
    : m_diff(dif, git_diff_free)
    , m_repo(std::move(repo))
{
}

int diff::foreach(
    diff_file_cb file_cb,
    diff_binary_cb binary_cb,
    diff_hunk_cb hunk_cb,
    diff_line_cb line_cb,
    void* payload
) const
{
  return git_diff_foreach(
      m_diff.get(), file_cb, binary_cb, hunk_cb, line_cb, payload
  );
}

diff diff::tree_to_tree(
    const tree& old, const tree& crnt, const git_diff_options* opts
)
{
  git_diff* dif = nullptr;

  if (git_diff_tree_to_tree(
          &dif, crnt.get_owner().get(), old.ptr(), crnt.ptr(), opts
      )
      != 0)
  {
    throw error<error_code_t::error>();
  }

  return {dif, old.get_owner()};
}

diff_stats::diff_stats(git_diff_stats* stats)
    : m_stats(stats, git_diff_stats_free)
{
}

diff_stats diff::get_stats() const
{
  git_diff_stats* stats = nullptr;

  if (git_diff_get_stats(&stats, m_diff.get()) != 0) {
    throw error<error_code_t::error>();
  }

  return diff_stats(stats);
}

size_t diff_stats::get_files_changed() const
{
  return git_diff_stats_files_changed(m_stats.get());
}

size_t diff_stats::get_insertions() const
{
  return git_diff_stats_insertions(m_stats.get());
}

size_t diff_stats::get_deletions() const
{
  return git_diff_stats_deletions(m_stats.get());
}

}  // namespace git2wrap

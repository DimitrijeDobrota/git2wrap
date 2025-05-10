#pragma once

#include <based/enum/enum_flag.hpp>
#include <based/types/types.hpp>
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

  [[nodiscard]] diff_stats get_stats() const;

  int foreach(
      diff_file_cb file_cb,
      diff_binary_cb binary_cb,
      diff_hunk_cb hunk_cb,
      diff_line_cb line_cb,
      void* payload
  ) const;

  static diff tree_to_tree(
      const tree& old, const tree& crnt, const git_diff_options* opts
  );

private:
  diffUPtr m_diff;
  repositoryPtr m_repo;
};

class GIT2WRAP_EXPORT diff_options
{
public:
  explicit diff_options()
  {
    git_diff_options_init(&m_options, GIT_DIFF_OPTIONS_VERSION);
  }

  operator auto() { return &m_options; }  // NOLINT(*explicit*)
  operator auto() const { return &m_options; }  // NOLINT(*explicit*)

  BASED_DECLARE_ENUM_FLAG(
      flag,
      based::u32,
      normal,
      reverse,
      include_ignored,
      recurse_ignored_dirs,
      include_untracked,
      recurse_untracked_dirs,
      include_unmodified,
      include_typechange,
      include_typechange_trees,
      ignore_filemode,
      ignore_submodules,
      ignore_case,
      include_casechange,
      disable_pathspec_match,
      skip_binary_check,
      enable_fast_untracked_dirs,
      update_index,
      include_unreadable,
      include_unreadable_as_untracked,
      indent_heuristic,
      ignore_blank_lines,
      force_text,
      force_binary,
      ignore_whitespace,
      ignore_whitespace_change,
      ignore_whitespace_eol,
      show_untracked_content,
      show_unmodified,
      flag_unused,
      patience,
      minimal,
      show_binary
  )

  auto flags() { return based::enum_flag_wrapper<flag::type>(m_options.flags); }

private:
  git_diff_options m_options = {};
};

BASED_DEFINE_ENUM_FLAG_CLASS(
    diff_options,
    flag,
    based::u32,
    normal,
    reverse,
    include_ignored,
    recurse_ignored_dirs,
    include_untracked,
    recurse_untracked_dirs,
    include_unmodified,
    include_typechange,
    include_typechange_trees,
    ignore_filemode,
    ignore_submodules,
    ignore_case,
    include_casechange,
    disable_pathspec_match,
    skip_binary_check,
    enable_fast_untracked_dirs,
    update_index,
    include_unreadable,
    include_unreadable_as_untracked,
    indent_heuristic,
    ignore_blank_lines,
    force_text,
    force_binary,
    ignore_whitespace,
    ignore_whitespace_change,
    ignore_whitespace_eol,
    show_untracked_content,
    show_unmodified,
    flag_unused,
    patience,
    minimal,
    show_binary
)

class GIT2WRAP_EXPORT diff_stats
{
public:
  explicit diff_stats(git_diff_stats* stats);

  [[nodiscard]] size_t get_files_changed() const;
  [[nodiscard]] size_t get_insertions() const;
  [[nodiscard]] size_t get_deletions() const;

private:
  diff_statsUPtr m_stats;
};

}  // namespace git2wrap

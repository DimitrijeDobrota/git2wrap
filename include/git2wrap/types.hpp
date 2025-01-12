#pragma once

#include <functional>
#include <memory>

#include <git2.h>

// NOLINTBEGIN
#define CLASS(T) \
  class T; \
  using T##Del = std::function<void(git_##T*)>; \
  using T##Ptr = std::shared_ptr<git_##T>; \
  using T##UPtr = std::unique_ptr<git_##T, T##Del>;
// NOLINTEND

namespace git2wrap
{

class branch;
class buf;
class libgit2;

CLASS(branch_iterator)
CLASS(commit)
CLASS(diff)
CLASS(object)
CLASS(oid)
CLASS(reference)
CLASS(repository)
CLASS(revwalk)
CLASS(signature)
CLASS(tag)
CLASS(tree)
CLASS(tree_entry)

using time_t = git_time_t;
using time = git_time;
using object_t = git_object_t;
using filemode_t = git_filemode_t;

using diff_options = git_diff_options;

using diff_binary_cb = git_diff_binary_cb;
using diff_file_cb = git_diff_file_cb;
using diff_hunk_cb = git_diff_hunk_cb;
using diff_line_cb = git_diff_line_cb;
using tag_foreach_cb = git_tag_foreach_cb;

static const struct empty_lambda_t  // static and const applies to the object!
{
  template<typename... T>
  void operator()(T&&...) const  // NOLINT
  {
  }  // does nothing
} empty_lambda {};  // declare an object which is static and const

}  // namespace git2wrap

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
CLASS(object)
CLASS(reference)
CLASS(repository)
CLASS(revwalk)
CLASS(signature)

using oid = git_oid;
using time_t = git_time_t;
using time = git_time;

}  // namespace git2wrap

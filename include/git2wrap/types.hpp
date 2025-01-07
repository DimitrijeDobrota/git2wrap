#pragma once

#include <memory>

#include <git2.h>

// NOLINTBEGIN
#define CLASS(T) \
  class T; \
  using T##Ptr = std::shared_ptr<git_##T>;
// NOLINTEND

namespace git2wrap
{

class const_signature;
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

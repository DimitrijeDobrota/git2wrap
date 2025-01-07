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

class branch;
class buf;
class libgit2;

CLASS(branch_iterator)
CLASS(commit)
CLASS(object)
CLASS(reference)
CLASS(repository)
CLASS(revwalk)

}  // namespace git2wrap

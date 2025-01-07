#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT commit
{
public:
  commit(git_commit* cmt, repositoryPtr repo);
  commit() = default;

  operator bool() const { return m_commit != nullptr; }  // NOLINT
  commitPtr get() const { return m_commit; }

  const git_oid* get_id() const;
  const char* get_summary() const;

private:
  commitPtr m_commit;
  repositoryPtr m_repo;
};

}  // namespace git2wrap

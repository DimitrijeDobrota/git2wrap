#pragma once

#include <git2.h>

#include "git2wrap/commit.hpp"
#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT revwalk
{
public:
  explicit revwalk(repositoryPtr repo);
  revwalk(revwalkPtr revwalk, repositoryPtr repo);

  operator bool() const { return m_revwalk != nullptr; }  // NOLINT
  revwalkPtr get() const { return m_revwalk; }

  void push(const git_oid* objid);
  void push_glob(const char* glob);
  void push_head();

  commit next();
  void reset();

private:
  revwalkPtr m_revwalk;
  repositoryPtr m_repo;
};

}  // namespace git2wrap

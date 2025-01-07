#pragma once

#include <functional>
#include <memory>

#include <git2.h>

#include "git2wrap/commit.hpp"
#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/repository.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT revwalk
{
public:
  explicit revwalk(repository& repo);

  void push(const git_oid* oid);
  void push_glob(const char* glob);
  void push_head();

  commit next();
  void reset();

  git_revwalk* get() { return m_revwalk.get(); }
  const git_revwalk* get() const { return m_revwalk.get(); }

private:
  using delete_f = std::function<void(git_revwalk*)>;
  std::unique_ptr<git_revwalk, delete_f> m_revwalk;
  repository* m_repo = nullptr;
};

}  // namespace git2wrap

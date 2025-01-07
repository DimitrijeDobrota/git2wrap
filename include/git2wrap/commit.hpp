#pragma once

#include <functional>
#include <memory>

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"

namespace git2wrap
{

class repository;

class GIT2WRAP_EXPORT commit
{
public:
  commit(git_commit* commit, repository& repo);
  commit() = default;

  operator bool() const { return m_commit != nullptr; }  // NOLINT

  git_commit* get() const { return m_commit.get(); }

  const git_oid* get_id() const;
  const char* get_summary() const;

private:
  using delete_f = std::function<void(git_commit*)>;
  std::unique_ptr<git_commit, delete_f> m_commit;
  repository* m_repo = nullptr;
};

}  // namespace git2wrap

#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/signature.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT tag
{
public:
  tag(git_tag* tagg, repositoryPtr repo);

  operator bool() const { return m_tag != nullptr; }  // NOLINT
  tag dup() const;

  const oid* get_id() const;
  repositoryPtr get_owner() const;
  const oid* get_target_id() const;
  object_t get_target_type() const;
  const char* get_name() const;
  signature get_tagger() const;
  const char* get_message() const;

private:
  tagUPtr m_tag;
  repositoryPtr m_repo;
};

}  // namespace git2wrap

#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/object.hpp"
#include "git2wrap/oid.hpp"
#include "git2wrap/signature.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT tag
{
public:
  tag(git_tag* tagg, repositoryPtr repo);

  operator bool() const { return m_tag != nullptr; }  // NOLINT
  [[nodiscard]] tag dup() const;

  [[nodiscard]] oid get_id() const;
  [[nodiscard]] repositoryPtr get_owner() const;
  [[nodiscard]] oid get_target_id() const;
  [[nodiscard]] object::object_t get_target_type() const;
  [[nodiscard]] const char* get_name() const;
  [[nodiscard]] signature get_tagger() const;
  [[nodiscard]] const char* get_message() const;

private:
  tagUPtr m_tag;
  repositoryPtr m_repo;
};

}  // namespace git2wrap

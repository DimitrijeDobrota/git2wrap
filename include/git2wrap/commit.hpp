#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/tree.hpp"
#include "git2wrap/types.hpp"
#include "git2wrap/oid.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT commit
{
public:
  commit(git_commit* cmt, repositoryPtr repo);
  commit() = default;

  operator bool() const { return m_commit != nullptr; }  // NOLINT
  commit dup() const;

  oid get_id() const;
  const char* get_summary() const;
  const char* get_message_encoding() const;
  const char* get_message() const;
  const char* get_message_raw() const;
  const char* get_body() const;
  time_t get_time() const;
  int get_time_offset() const;
  signature get_signature() const;
  signature get_author() const;
  const char* get_raw_header() const;
  unsigned get_parentcount() const;
  commit get_parent(unsigned n = 0) const;
  buf get_header_field(const char* field) const;

  tree get_tree() const;

private:
  commitUPtr m_commit;
  repositoryPtr m_repo;
};

}  // namespace git2wrap

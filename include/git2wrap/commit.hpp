#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/oid.hpp"
#include "git2wrap/tree.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT commit
{
public:
  commit(git_commit* cmt, repositoryPtr repo);
  commit() = default;

  operator bool() const { return m_commit != nullptr; }  // NOLINT
  [[nodiscard]] commit dup() const;

  [[nodiscard]] oid get_id() const;
  [[nodiscard]] const char* get_summary() const;
  [[nodiscard]] const char* get_message_encoding() const;
  [[nodiscard]] const char* get_message() const;
  [[nodiscard]] const char* get_message_raw() const;
  [[nodiscard]] const char* get_body() const;
  [[nodiscard]] time_t get_time() const;
  [[nodiscard]] int get_time_offset() const;
  [[nodiscard]] signature get_signature() const;
  [[nodiscard]] signature get_author() const;
  [[nodiscard]] const char* get_raw_header() const;
  [[nodiscard]] unsigned get_parentcount() const;
  [[nodiscard]] commit get_parent(unsigned n = 0) const;
  [[nodiscard]] buf get_header_field(const char* field) const;

  [[nodiscard]] tree get_tree() const;

private:
  commitUPtr m_commit;
  repositoryPtr m_repo;
};

}  // namespace git2wrap

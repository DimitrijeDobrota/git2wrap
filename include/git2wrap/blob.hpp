#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/oid.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT blob
{
public:
  blob(git_blob* blb, repositoryPtr repo);

  operator bool() const { return m_blob != nullptr; }  // NOLINT
  [[nodiscard]] blob dup() const;

  [[nodiscard]] oid get_id() const;
  [[nodiscard]] repositoryPtr get_owner() const;
  [[nodiscard]] const void* get_rawcontent() const;
  [[nodiscard]] object_size_t get_rawsize() const;
  [[nodiscard]] bool is_binary() const;

private:
  blobUPtr m_blob;
  repositoryPtr m_repo;
};

}  // namespace git2wrap

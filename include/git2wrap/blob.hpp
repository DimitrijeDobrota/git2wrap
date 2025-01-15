#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/types.hpp"
#include "git2wrap/oid.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT blob
{
public:
  blob(git_blob* blb, repositoryPtr repo);

  operator bool() const { return m_blob != nullptr; }  // NOLINT
  blob dup() const;

  oid get_id() const;
  repositoryPtr get_owner() const;
  const void* get_rawcontent() const;
  object_size_t get_rawsize() const;
  bool is_binary() const;

private:
  blobUPtr m_blob;
  repositoryPtr m_repo;
};

}  // namespace git2wrap

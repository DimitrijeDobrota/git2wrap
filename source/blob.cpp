#include "git2wrap/blob.hpp"

#include "git2wrap/error.hpp"

namespace git2wrap
{

blob::blob(git_blob* blb, repositoryPtr repo)
    : m_blob(blb, git_blob_free)
    , m_repo(std::move(repo))
{
}

blob blob::dup() const
{
  git_blob* blb = nullptr;

  if (auto err = git_blob_dup(&blb, m_blob.get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return {blb, m_repo};
}

oid blob::get_id() const
{
  return oid(git_blob_id(m_blob.get()));
}

repositoryPtr blob::get_owner() const
{
  return m_repo;
}

const void* blob::get_rawcontent() const
{
  return git_blob_rawcontent(m_blob.get());
}

object_size_t blob::get_rawsize() const
{
  return git_blob_rawsize(m_blob.get());
}

bool blob::is_binary() const
{
  return git_blob_is_binary(m_blob.get()) == 1;
}

}  // namespace git2wrap

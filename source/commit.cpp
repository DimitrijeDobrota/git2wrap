#include "git2wrap/commit.hpp"

#include "git2wrap/buf.hpp"
#include "git2wrap/error.hpp"
#include "git2wrap/signature.hpp"

namespace git2wrap
{

commit::commit(git_commit* cmt, repositoryPtr repo)
    : m_commit(cmt, git_commit_free)
    , m_repo(std::move(repo))
{
}

commit commit::dup() const
{
  git_commit* cmt = nullptr;

  if (auto err = git_commit_dup(&cmt, m_commit.get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return {cmt, m_repo};
}

const git_oid* commit::get_id() const
{
  return git_commit_id(m_commit.get());
}

const char* commit::get_summary() const
{
  return git_commit_summary(m_commit.get());
}

const char* commit::get_message_encoding() const
{
  return git_commit_message_encoding(m_commit.get());
}

const char* commit::get_message() const
{
  return git_commit_message(m_commit.get());
}

const char* commit::get_message_raw() const
{
  return git_commit_message_raw(m_commit.get());
}

const char* commit::get_body() const
{
  return git_commit_body(m_commit.get());
}

time_t commit::get_time() const
{
  return git_commit_time(m_commit.get());
}

int commit::get_time_offset() const
{
  return git_commit_time_offset(m_commit.get());
}

signature commit::get_signature() const
{
  return signature(git_commit_committer(m_commit.get()));
}

signature commit::get_author() const
{
  return signature(git_commit_author(m_commit.get()));
}

const char* commit::get_raw_header() const
{
  return git_commit_raw_header(m_commit.get());
}

unsigned commit::get_parentcount() const
{
  return git_commit_parentcount(m_commit.get());
}

commit commit::get_parent(unsigned n) const
{
  git_commit* cmt = nullptr;

  if (auto err = git_commit_parent(&cmt, m_commit.get(), n)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return {cmt, m_repo};
}

buf commit::get_header_field(const char* field) const
{
  buf bufr;

  if (auto err = git_commit_header_field(bufr.get(), m_commit.get(), field)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return bufr;
}

}  // namespace git2wrap

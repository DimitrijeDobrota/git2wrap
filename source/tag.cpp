#include "git2wrap/tag.hpp"

#include "git2wrap/error.hpp"

namespace git2wrap
{

tag::tag(git_tag* tagg, repositoryPtr repo)
    : m_tag(tagg, git_tag_free)
    , m_repo(std::move(repo))
{
}

tag tag::dup() const
{
  git_tag* tagg = nullptr;
  git_tag_dup(&tagg, m_tag.get());
  return {tagg, m_repo};
}

oid tag::get_id() const
{
  return oid(git_tag_id(m_tag.get()));
}

repositoryPtr tag::get_owner() const
{
  return m_repo;
}

oid tag::get_target_id() const
{
  return oid(git_tag_target_id(m_tag.get()));
}

object::object_t tag::get_target_type() const
{
  return object::object_t::get(git_tag_target_type(m_tag.get()));
}

const char* tag::get_name() const
{
  return git_tag_name(m_tag.get());
}

signature tag::get_tagger() const
{
  return signature(git_tag_tagger(m_tag.get()));
}

const char* tag::get_message() const
{
  return git_tag_message(m_tag.get());
}

}  // namespace git2wrap

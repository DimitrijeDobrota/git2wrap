#include "git2wrap/object.hpp"

#include "git2wrap/error.hpp"

namespace git2wrap
{

object::object(git_object* obj, repositoryPtr repo)
    : m_obj(obj, git_object_free)
    , m_repo(std::move(repo))
{
}

object object::dup() const
{
  git_object* obj = nullptr;
  git_object_dup(&obj, m_obj.get());
  return {obj, m_repo};
}

oid object::get_id() const
{
  return oid(git_object_id(m_obj.get()));
}

buf object::get_id_short() const
{
  buf bufr;

  if (git_object_short_id(bufr.get(), m_obj.get()) != 0) {
    throw error<error_code_t::error>();
  }

  return bufr;
}

object::object_t object::get_type() const
{
  return object_t::get(git_object_type(m_obj.get()));
}

repositoryPtr object::get_owner() const
{
  return m_repo;
}

const char* object::type2string(object_t type)
{
  return git_object_type2string(git_object_t(type.value));
}

object::object_t object::string2type(const char* str)
{
  return object_t::get(git_object_string2type(str));
}

}  // namespace git2wrap

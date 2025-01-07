#include "git2wrap/object.hpp"

#include "git2wrap/error.hpp"

namespace git2wrap
{

object::object(git_object* obj, repositoryPtr repo)
    : m_obj(obj, git_object_free)
    , m_repo(std::move(repo))
{
}

const oid* object::get_id() const
{
  return git_object_id(m_obj.get());
}

object object::clone()
{
  git_object* obj = nullptr;

  if (auto err = git_object_dup(&obj, m_obj.get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return {obj, m_repo};
}

buf object::get_id_short() const
{
  buf bufr;

  if (auto err = git_object_short_id(bufr.get(), m_obj.get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return bufr;
}

object::object_t object::get_type() const
{
  return git_object_type(m_obj.get());
}

repositoryPtr object::get_owner() const
{
  return m_repo;
}

const char* object::type2string(object_t type)
{
  return git_object_type2string(type);
}

object::object_t object::string2type(const char* str)
{
  return git_object_string2type(str);
}

}  // namespace git2wrap

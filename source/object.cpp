#include "git2wrap/object.hpp"

#include "git2wrap/error.hpp"

namespace git2wrap
{

object::object(git_object* obj)
    : m_obj(obj, git_object_free)
{
}

const oid* object::get_id() const
{
  return git_object_id(m_obj.get());
}

object object::clone()
{
  git_object* obj = nullptr;

  if (auto err = git_object_dup(&obj, get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return object(obj);
}

buf object::get_id_short() const
{
  buf bufr;

  if (auto err = git_object_short_id(bufr.get(), get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return bufr;
}

object::object_t object::get_type() const
{
  return git_object_type(get());
}

/*
repository object::get_owner() const
{
  return repository(git_object_owner(get()));
}
*/

const char* object::type2string(object_t type)
{
  return git_object_type2string(type);
}

object::object_t object::string2type(const char* str)
{
  return git_object_string2type(str);
}

}  // namespace git2wrap

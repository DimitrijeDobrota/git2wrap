#pragma once

#include <functional>
#include <memory>

#include <git2.h>

#include "git2wrap/buf.hpp"
#include "git2wrap/git2wrap_export.hpp"

namespace git2wrap
{

using oid = git_oid;

class GIT2WRAP_EXPORT object
{
public:
  using object_t = git_object_t;

  explicit object(git_object* obj);

  git_object* get() { return m_obj.get(); }
  const git_object* get() const { return m_obj.get(); }

  object clone();

  const oid* get_id() const;
  buf get_id_short() const;
  object_t get_type() const;
  // repository get_owner() const;

  static const char *type2string(object_t type);
  static git_object_t string2type(const char *str); 

private:
  using delete_f = std::function<void(git_object*)>;
  std::unique_ptr<git_object, delete_f> m_obj;
};

}  // namespace git2wrap

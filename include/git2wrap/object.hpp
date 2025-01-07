#pragma once

#include <git2.h>

#include "git2wrap/buf.hpp"
#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

using oid = git_oid;

class GIT2WRAP_EXPORT object
{
public:
  using object_t = git_object_t;

  object(git_object* obj, repositoryPtr repo);
  object() = default;

  operator bool() const { return m_obj != nullptr; }  // NOLINT
  objectPtr get() const { return m_obj; }

  object clone();

  const oid* get_id() const;
  buf get_id_short() const;
  object_t get_type() const;
  repositoryPtr get_owner() const;

  static const char* type2string(object_t type);
  static git_object_t string2type(const char* str);

private:
  objectPtr m_obj;
  repositoryPtr m_repo;
};

}  // namespace git2wrap

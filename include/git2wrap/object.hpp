#pragma once

#include <git2.h>

#include "git2wrap/buf.hpp"
#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/oid.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT object
{
public:
  using object_t = git_object_t;

  object(git_object* obj, repositoryPtr repo);
  object() = default;

  operator bool() const { return m_obj != nullptr; }  // NOLINT
  [[nodiscard]] object dup() const;

  [[nodiscard]] oid get_id() const;
  [[nodiscard]] buf get_id_short() const;
  [[nodiscard]] object_t get_type() const;
  [[nodiscard]] repositoryPtr get_owner() const;

  static const char* type2string(object_t type);
  static git_object_t string2type(const char* str);

private:
  objectUPtr m_obj;
  repositoryPtr m_repo;
};

}  // namespace git2wrap

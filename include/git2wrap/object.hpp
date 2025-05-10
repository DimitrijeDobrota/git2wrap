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
  object(git_object* obj, repositoryPtr repo);
  object() = default;

  operator bool() const { return m_obj != nullptr; }  // NOLINT
  [[nodiscard]] object dup() const;

  BASED_DECLARE_ENUM(
      object_type, int, -2, any, invalid, commit, unused, tree, blob, tag
  )

  using object_t = object_type::type;

  [[nodiscard]] oid get_id() const;
  [[nodiscard]] buf get_id_short() const;
  [[nodiscard]] object_t get_type() const;
  [[nodiscard]] repositoryPtr get_owner() const;

  static const char* type2string(object_t type);
  static object_t string2type(const char* str);

private:
  objectUPtr m_obj;
  repositoryPtr m_repo;
};

BASED_DEFINE_ENUM_CLASS(
    object, object_type, int, -2, any, invalid, commit, unused, tree, blob, tag
)

}  // namespace git2wrap

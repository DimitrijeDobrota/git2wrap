#pragma once

#include <stdexcept>
#include <string>

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"

namespace git2wrap
{

enum class error_code_t  // NOLINT
{
  ok = GIT_OK,
  error = GIT_ERROR,
  enotfound = GIT_ENOTFOUND,
  eexists = GIT_EEXISTS,
  eambiguous = GIT_EAMBIGUOUS,
  ebufs = GIT_EBUFS,
  euser = GIT_EUSER,
  ebarerepo = GIT_EBAREREPO,
  eunbornbranch = GIT_EUNBORNBRANCH,
  eunmerged = GIT_EUNMERGED,
  enonfastforward = GIT_ENONFASTFORWARD,
  einvalidspec = GIT_EINVALIDSPEC,
  econflict = GIT_ECONFLICT,
  elocked = GIT_ELOCKED,
  emodified = GIT_EMODIFIED,
  eauth = GIT_EAUTH,
  ecertificate = GIT_ECERTIFICATE,
  eapplied = GIT_EAPPLIED,
  epeel = GIT_EPEEL,
  eeof = GIT_EEOF,
  einvalid = GIT_EINVALID,
  euncommitted = GIT_EUNCOMMITTED,
  edirectory = GIT_EDIRECTORY,
  emergeconflict = GIT_EMERGECONFLICT,
  passthrough = GIT_PASSTHROUGH,
  iterover = GIT_ITEROVER,
  retry = GIT_RETRY,
  emismatch = GIT_EMISMATCH,
  eindexdirty = GIT_EINDEXDIRTY,
  eapplyfail = GIT_EAPPLYFAIL,
  eowner = GIT_EOWNER,
  timeout = GIT_TIMEOUT,
  eunchanged = GIT_EUNCHANGED,
  enotsupported = GIT_ENOTSUPPORTED,
  ereadonly = GIT_EREADONLY,
};

enum class error_t  // NOLINT
{
  none = GIT_ERROR_NONE,
  nomemory = GIT_ERROR_NOMEMORY,
  os = GIT_ERROR_OS,
  invalid = GIT_ERROR_INVALID,
  reference = GIT_ERROR_REFERENCE,
  zlib = GIT_ERROR_ZLIB,
  repository = GIT_ERROR_REPOSITORY,
  config = GIT_ERROR_CONFIG,
  regex = GIT_ERROR_REGEX,
  odb = GIT_ERROR_ODB,
  index = GIT_ERROR_INDEX,
  object = GIT_ERROR_OBJECT,
  net = GIT_ERROR_NET,
  tag = GIT_ERROR_TAG,
  tree = GIT_ERROR_TREE,
  indexer = GIT_ERROR_INDEXER,
  ssl = GIT_ERROR_SSL,
  submodule = GIT_ERROR_SUBMODULE,
  thread = GIT_ERROR_THREAD,
  stash = GIT_ERROR_STASH,
  checkout = GIT_ERROR_CHECKOUT,
  fetchhead = GIT_ERROR_FETCHHEAD,
  merge = GIT_ERROR_MERGE,
  ssh = GIT_ERROR_SSH,
  filter = GIT_ERROR_FILTER,
  revert = GIT_ERROR_REVERT,
  callback = GIT_ERROR_CALLBACK,
  cherrypick = GIT_ERROR_CHERRYPICK,
  describe = GIT_ERROR_DESCRIBE,
  rebase = GIT_ERROR_REBASE,
  filesystem = GIT_ERROR_FILESYSTEM,
  patch = GIT_ERROR_PATCH,
  worktree = GIT_ERROR_WORKTREE,
  sha = GIT_ERROR_SHA,
  http = GIT_ERROR_HTTP,
  internal = GIT_ERROR_INTERNAL,
  grafts = GIT_ERROR_GRAFTS,
};

static inline std::string error_get_message(error_code_t error)
{
  switch (error) {
    case error_code_t::ok:
      return "No error occurred; the call was successful.";
    case error_code_t::error:
      return "An error occurred; call git_error_last for more information.";
    case error_code_t::enotfound:
      return "Requested object could not be found.";
    case error_code_t::eexists:
      return "Object exists preventing operation.";
    case error_code_t::eambiguous:
      return "More than one object matches.";
    case error_code_t::ebufs:
      return "Output buffer too short to hold data.";
    case error_code_t::euser:
      return "callback generated";
    case error_code_t::ebarerepo:
      return "Operation not allowed on bare repository.";
    case error_code_t::eunbornbranch:
      return "HEAD refers to branch with no commits.";
    case error_code_t::eunmerged:
      return "Merge in progress prevented operation";
    case error_code_t::enonfastforward:
      return "Reference was not fast-forwardable";
    case error_code_t::einvalidspec:
      return "Name/ref spec was not in a valid format";
    case error_code_t::econflict:
      return "Checkout conflicts prevented operation";
    case error_code_t::elocked:
      return "Lock file prevented operation";
    case error_code_t::emodified:
      return "Reference value does not match expected";
    case error_code_t::eauth:
      return "Authentication error";
    case error_code_t::ecertificate:
      return "Server certificate is invalid";
    case error_code_t::eapplied:
      return "Patch/merge has already been applied";
    case error_code_t::epeel:
      return "The requested peel operation is not possible";
    case error_code_t::eeof:
      return "Unexpected EOF";
    case error_code_t::einvalid:
      return "Invalid operation or input";
    case error_code_t::euncommitted:
      return "Uncommitted changes in index prevented operation";
    case error_code_t::edirectory:
      return "The operation is not valid for a directory";
    case error_code_t::emergeconflict:
      return "A merge conflict exists and cannot continue";
    case error_code_t::passthrough:
      return "A user-configured callback refused to act";
    case error_code_t::iterover:
      return "Signals end of iteration with iterator";
    case error_code_t::retry:
      return "Internal only";
    case error_code_t::emismatch:
      return "Hashsum mismatch in object";
    case error_code_t::eindexdirty:
      return "Unsaved changes in the index would be overwritten";
    case error_code_t::eapplyfail:
      return "Patch application failed";
    case error_code_t::eowner:
      return "The object is not owned by the current user";
    case error_code_t::timeout:
      return "The operation timed out";
    case error_code_t::eunchanged:
      return "There were no changes";
    case error_code_t::enotsupported:
      return "An option is not supported";
    case error_code_t::ereadonly:
      return "The subject is read-only";
  }

  return "git2wrap error, should not happen...";
}

class GIT2WRAP_EXPORT runtime_error : public std::runtime_error
{
public:
  explicit runtime_error(const std::string& err)
      : std::runtime_error(err)
  {
  }
};

template<error_code_t e>
class GIT2WRAP_EXPORT error : public runtime_error
{
public:
  explicit error()
      : runtime_error(error_get_message(e))
  {
  }

private:
};

template<>
class GIT2WRAP_EXPORT error<error_code_t::error> : public runtime_error
{
public:
  explicit error()
      : runtime_error(git_error_last()->message)
      , m_err(static_cast<error_t>(git_error_last()->klass))
  {
  }

  [[nodiscard]] error_t get_error() const { return m_err; }

private:
  error_t m_err;
};

}  // namespace git2wrap

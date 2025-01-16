#pragma once

#include <stdexcept>
#include <string>

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"

namespace git2wrap
{

enum error_code_t  // NOLINT
{
  OK = GIT_OK,
  ERROR = GIT_ERROR,
  ENOTFOUND = GIT_ENOTFOUND,
  EEXISTS = GIT_EEXISTS,
  EAMBIGUOUS = GIT_EAMBIGUOUS,
  EBUFS = GIT_EBUFS,
  EUSER = GIT_EUSER,
  EBAREREPO = GIT_EBAREREPO,
  EUNBORNBRANCH = GIT_EUNBORNBRANCH,
  EUNMERGED = GIT_EUNMERGED,
  ENONFASTFORWARD = GIT_ENONFASTFORWARD,
  EINVALIDSPEC = GIT_EINVALIDSPEC,
  ECONFLICT = GIT_ECONFLICT,
  ELOCKED = GIT_ELOCKED,
  EMODIFIED = GIT_EMODIFIED,
  EAUTH = GIT_EAUTH,
  ECERTIFICATE = GIT_ECERTIFICATE,
  EAPPLIED = GIT_EAPPLIED,
  EPEEL = GIT_EPEEL,
  EEOF = GIT_EEOF,
  EINVALID = GIT_EINVALID,
  EUNCOMMITTED = GIT_EUNCOMMITTED,
  EDIRECTORY = GIT_EDIRECTORY,
  EMERGECONFLICT = GIT_EMERGECONFLICT,
  PASSTHROUGH = GIT_PASSTHROUGH,
  ITEROVER = GIT_ITEROVER,
  RETRY = GIT_RETRY,
  EMISMATCH = GIT_EMISMATCH,
  EINDEXDIRTY = GIT_EINDEXDIRTY,
  EAPPLYFAIL = GIT_EAPPLYFAIL,
  EOWNER = GIT_EOWNER,
  TIMEOUT = GIT_TIMEOUT,
  EUNCHANGED = GIT_EUNCHANGED,
  ENOTSUPPORTED = GIT_ENOTSUPPORTED,
  EREADONLY = GIT_EREADONLY,
};

enum error_t  // NOLINT
{
  NONE = GIT_ERROR_NONE,
  NOMEMORY = GIT_ERROR_NOMEMORY,
  OS = GIT_ERROR_OS,
  INVALID = GIT_ERROR_INVALID,
  REFERENCE = GIT_ERROR_REFERENCE,
  ZLIB = GIT_ERROR_ZLIB,
  REPOSITORY = GIT_ERROR_REPOSITORY,
  CONFIG = GIT_ERROR_CONFIG,
  REGEX = GIT_ERROR_REGEX,
  ODB = GIT_ERROR_ODB,
  INDEX = GIT_ERROR_INDEX,
  OBJECT = GIT_ERROR_OBJECT,
  NET = GIT_ERROR_NET,
  TAG = GIT_ERROR_TAG,
  TREE = GIT_ERROR_TREE,
  INDEXER = GIT_ERROR_INDEXER,
  SSL = GIT_ERROR_SSL,
  SUBMODULE = GIT_ERROR_SUBMODULE,
  THREAD = GIT_ERROR_THREAD,
  STASH = GIT_ERROR_STASH,
  CHECKOUT = GIT_ERROR_CHECKOUT,
  FETCHHEAD = GIT_ERROR_FETCHHEAD,
  MERGE = GIT_ERROR_MERGE,
  SSH = GIT_ERROR_SSH,
  FILTER = GIT_ERROR_FILTER,
  REVERT = GIT_ERROR_REVERT,
  CALLBACK = GIT_ERROR_CALLBACK,
  CHERRYPICK = GIT_ERROR_CHERRYPICK,
  DESCRIBE = GIT_ERROR_DESCRIBE,
  REBASE = GIT_ERROR_REBASE,
  FILESYSTEM = GIT_ERROR_FILESYSTEM,
  PATCH = GIT_ERROR_PATCH,
  WORKTREE = GIT_ERROR_WORKTREE,
  SHA = GIT_ERROR_SHA,
  HTTP = GIT_ERROR_HTTP,
  INTERNAL = GIT_ERROR_INTERNAL,
  GRAFTS = GIT_ERROR_GRAFTS,
};

static inline std::string error_get_message(error_code_t error)
{
  switch (error) {
    case error_code_t::OK:
      return "No error occurred; the call was successful.";
    case error_code_t::ERROR:
      return "An error occurred; call git_error_last for more information.";
    case error_code_t::ENOTFOUND:
      return "Requested object could not be found.";
    case error_code_t::EEXISTS:
      return "Object exists preventing operation.";
    case error_code_t::EAMBIGUOUS:
      return "More than one object matches.";
    case error_code_t::EBUFS:
      return "Output buffer too short to hold data.";
    case error_code_t::EUSER:
      return "callback generated";
    case error_code_t::EBAREREPO:
      return "Operation not allowed on bare repository.";
    case error_code_t::EUNBORNBRANCH:
      return "HEAD refers to branch with no commits.";
    case error_code_t::EUNMERGED:
      return "Merge in progress prevented operation";
    case error_code_t::ENONFASTFORWARD:
      return "Reference was not fast-forwardable";
    case error_code_t::EINVALIDSPEC:
      return "Name/ref spec was not in a valid format";
    case error_code_t::ECONFLICT:
      return "Checkout conflicts prevented operation";
    case error_code_t::ELOCKED:
      return "Lock file prevented operation";
    case error_code_t::EMODIFIED:
      return "Reference value does not match expected";
    case error_code_t::EAUTH:
      return "Authentication error";
    case error_code_t::ECERTIFICATE:
      return "Server certificate is invalid";
    case error_code_t::EAPPLIED:
      return "Patch/merge has already been applied";
    case error_code_t::EPEEL:
      return "The requested peel operation is not possible";
    case error_code_t::EEOF:
      return "Unexpected EOF";
    case error_code_t::EINVALID:
      return "Invalid operation or input";
    case error_code_t::EUNCOMMITTED:
      return "Uncommitted changes in index prevented operation";
    case error_code_t::EDIRECTORY:
      return "The operation is not valid for a directory";
    case error_code_t::EMERGECONFLICT:
      return "A merge conflict exists and cannot continue";
    case error_code_t::PASSTHROUGH:
      return "A user-configured callback refused to act";
    case error_code_t::ITEROVER:
      return "Signals end of iteration with iterator";
    case error_code_t::RETRY:
      return "Internal only";
    case error_code_t::EMISMATCH:
      return "Hashsum mismatch in object";
    case error_code_t::EINDEXDIRTY:
      return "Unsaved changes in the index would be overwritten";
    case error_code_t::EAPPLYFAIL:
      return "Patch application failed";
    case error_code_t::EOWNER:
      return "The object is not owned by the current user";
    case error_code_t::TIMEOUT:
      return "The operation timed out";
    case error_code_t::EUNCHANGED:
      return "There were no changes";
    case error_code_t::ENOTSUPPORTED:
      return "An option is not supported";
    case error_code_t::EREADONLY:
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

template<error_code_t E>
class GIT2WRAP_EXPORT error : public runtime_error
{
public:
  explicit error()
      : runtime_error(error_get_message(E))
  {
  }

private:
};

template<>
class GIT2WRAP_EXPORT error<error_code_t::ERROR> : public runtime_error
{
public:
  explicit error()
      : runtime_error(git_error_last()->message)
      , m_err(static_cast<error_t>(git_error_last()->klass))
  {
  }

  error_t get_error() const { return m_err; }

private:
  error_t m_err;
};

}  // namespace git2wrap

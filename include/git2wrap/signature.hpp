#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT signature
{
public:
  explicit signature(const git_signature* sig);
  explicit signature(git_signature* sig);

  operator bool() const { return m_sig != nullptr; }  // NOLINT
  signature dup() const;

  const char* get_email() const { return m_sig->email; }
  const char* get_name() const { return m_sig->name; }
  time get_time() const { return m_sig->when; }

private:
  signatureUPtr m_sig;
};

}  // namespace git2wrap

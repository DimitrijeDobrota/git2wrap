#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT signature
{
public:
  explicit signature(git_signature* sig);

  operator bool() const { return m_sig != nullptr; }  // NOLINT
  signaturePtr get() const { return m_sig; }

  const char* get_email() const { return m_sig->email; }
  const char* get_name() const { return m_sig->name; }
  time get_time() const { return m_sig->when; }

private:
  signaturePtr m_sig;
};

class GIT2WRAP_EXPORT const_signature
{
public:
  explicit const_signature(const git_signature* sig);

  operator bool() const { return m_sig != nullptr; }  // NOLINT
  const git_signature* get() const { return m_sig; }

  const char* get_email() const { return m_sig->email; }
  const char* get_name() const { return m_sig->name; }
  time get_time() const { return m_sig->when; }

private:
  const git_signature* m_sig;
};

}  // namespace git2wrap

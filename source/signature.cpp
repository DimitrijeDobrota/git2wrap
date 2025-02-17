#include "git2wrap/signature.hpp"

#include "git2wrap/error.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

signature::signature(const git_signature* sig)
    : m_sig(const_cast<git_signature*>(sig), empty_lambda)  // NOLINT
{
}

signature::signature(git_signature* sig)
    : m_sig(sig, git_signature_free)
{
}

signature signature::dup() const
{
  git_signature* sig = nullptr;
  git_signature_dup(&sig, m_sig.get());
  return signature(sig);
}

}  // namespace git2wrap

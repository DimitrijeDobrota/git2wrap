#include "git2wrap/signature.hpp"

namespace git2wrap
{

signature::signature(git_signature* sig)
    : m_sig(sig, git_signature_free)
{
}

const_signature::const_signature(const git_signature* sig)
    : m_sig(sig)
{
}

}  // namespace git2wrap

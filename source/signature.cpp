#include "git2wrap/signature.hpp"

#include "git2wrap/error.hpp"

static const struct empty_lambda_t  // static and const applies to the object!
{
  template<typename... T>
  void operator()(T&&...) const  // NOLINT
  {
  }  // does nothing
} empty_lambda {};  // declare an object which is static and const

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

  if (auto err = git_signature_dup(&sig, m_sig.get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return signature(sig);
}

}  // namespace git2wrap

#include "git2wrap/oid.hpp"

#include "git2wrap/error.hpp"

namespace git2wrap
{

oid::oid(const git_oid* objid)
    : m_oid(const_cast<git_oid*>(objid), empty_lambda)  // NOLINT
{
}

std::string oid::get_hex_string(size_t n)
{
  std::string str(n, 0);
  char* bfr = const_cast<char*>(str.c_str());  // NOLINT

  if (git_oid_tostr(bfr, n + 1, m_oid.get()) == nullptr) {
    throw error(0, git_error_last(), __FILE__, __LINE__);
  }

  return str;
}

}  // namespace git2wrap

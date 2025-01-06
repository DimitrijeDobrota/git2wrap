#include "git2wrap/buf.hpp"

namespace git2wrap
{

buf::~buf()
{
  git_buf_dispose(get());
}

}  // namespace git2wrap

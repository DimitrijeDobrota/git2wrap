#include <format>
#include <iostream>

#include "git2wrap/error.hpp"
#include "git2wrap/libgit2.hpp"

int main()
{
  try {
    using namespace git2wrap;  // NOLINT

    const libgit2 git;

  } catch (const git2wrap::error& err) {
    std::cerr << std::format("Error %d/%d: %s\n",
                             err.get_error(),
                             err.get_klass(),
                             err.get_message());
  }

  return 0;
}

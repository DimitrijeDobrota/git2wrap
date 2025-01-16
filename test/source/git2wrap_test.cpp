#include <format>
#include <iostream>

#include "git2wrap/error.hpp"
#include "git2wrap/libgit2.hpp"

int main()
{
  try {
    using namespace git2wrap;  // NOLINT

    const libgit2 git;

  } catch (const git2wrap::runtime_error& err) {
    std::cerr << std::format("Error: %s\n", err.what());
  }

  return 0;
}

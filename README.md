# git2wrap

C++ 20 wrapper for libgit2

## Description

This project is a C++ wrapper of famous libgit2 library.

I plan to add features as they are needed for my other projects, so It's still
a long way until full coverage.


## Dependencies

* CMake 3.14 or latter
* Compiler with C++20 support (tested: clang 18.1.8, gcc 14.2.1)
* [`libgit2 1.9`](https://github.com/libgit2/libgit2)


## Building and installing

See the [`BUILDING`](BUILDING.md) document.


## Usage

> Please reference [startgit](https://github.com/DimitrijeDobrota/startgit) for relevant usage example


## Version History

- 0.2
    * Working with repository, branches, commits and diffs
    * Implement exception mechanism around error codes
- 0.1
    * Initial development phase
    * Heavy exploration


## Contributing

See the [`CONTRIBUTING`](CONTRIBUTING.md) document.


# Licensing

This project is licensed under the MIT License
- see the [`LICENSE`](LICENSE.md) document for details


## Acknowledgments

Inspiration, code snippets, etc.
* [`cppgit2`](https://github.com/p-ranav/cppgit2)
* [`libgit2cpp`](https://github.com/AndreyG/libgit2cpp)

#pragma once

#include <exception>
#include <string>

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT error : public std::exception
{
public:
  explicit error(int err, const git_error* git_err)
      : m_error(err)
      , m_klass(git_err->klass)
      , m_message(git_err->message)
  {
  }

  const char* get_message() const { return m_message.c_str(); }
  int get_klass() const { return m_klass; }
  int get_error() const { return m_error; }

private:
  int m_error;
  int m_klass;
  std::string m_message;
};

class GIT2WRAP_EXPORT libgit2
{
public:
  libgit2();
  ~libgit2();

  libgit2(const libgit2&) = delete;
  libgit2(libgit2&&) = delete;
  libgit2& operator=(const libgit2&) = delete;
  libgit2& operator=(libgit2&&) = delete;

private:
  int m_cinit = 0;
};

class GIT2WRAP_EXPORT repository
{
public:
  using init_options = git_repository_init_options;
  using clone_options = git_clone_options;

  explicit repository(git_repository* repo);
  repository(const char* path, unsigned is_bare);
  repository(const char* path, init_options* opts);
  ~repository();

  repository(const repository&) = delete;
  repository(repository&&) = delete;
  repository& operator=(const repository&) = delete;
  repository& operator=(repository&&) = delete;

  static repository clone(const char* url,
                          const char* local_path,
                          const clone_options* options);

  static repository open(const char* path);
  static repository open(const char* path,
                         unsigned flags,
                         const char* ceiling_dirs);

private:
  git_repository* m_repo = nullptr;
};

}  // namespace git2wrap

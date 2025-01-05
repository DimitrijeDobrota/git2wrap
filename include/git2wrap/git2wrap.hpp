#pragma once

#include <exception>
#include <functional>
#include <memory>
#include <string>

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT error : public std::exception
{
public:
  explicit error(int err,
                 const git_error* git_err,
                 const char* file,
                 unsigned line)
      : m_error(err)
      , m_klass(git_err->klass)
      , m_message(git_err->message)
      , m_file(file)
      , m_line(line)
  {
  }

  int get_klass() const { return m_klass; }
  int get_error() const { return m_error; }
  unsigned get_line() const { return m_line; }
  const char* get_file() const { return m_file; }
  const char* get_message() const { return m_message.c_str(); }

private:
  int m_error;
  int m_klass;
  std::string m_message;
  const char* m_file;
  unsigned m_line;
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

class GIT2WRAP_EXPORT reference
{
public:
  explicit reference(git_reference* ref = nullptr);

  git_reference* get() const;

private:
  std::unique_ptr<git_reference, std::function<void(git_reference*)>> m_ref;
};

class GIT2WRAP_EXPORT branch
{
public:
  explicit branch(git_reference* ref = nullptr,
                  git_branch_t type = git_branch_t(0));

  git_branch_t get_type() const { return m_type; }
  git_reference* get_reference() const { return m_ref.get(); }

  const std::string& get_name();

private:
  reference m_ref;
  git_branch_t m_type = {};

  std::string m_name;
};

class GIT2WRAP_EXPORT repository
{
public:
  using init_options = git_repository_init_options;
  using clone_options = git_clone_options;

  explicit repository(git_repository* repo);
  repository(const char* path, unsigned is_bare);
  repository(const char* path, init_options* opts);

  static repository clone(const char* url,
                          const char* local_path,
                          const clone_options* options);

  static repository open(const char* path);
  static repository open(const char* path,
                         unsigned flags,
                         const char* ceiling_dirs);

  struct branch_iterator
  {
    explicit branch_iterator(git_branch_iterator* iter);
    branch_iterator() = default;

    branch_iterator(const branch_iterator&) = delete;
    branch_iterator& operator=(const branch_iterator&) = delete;

    branch_iterator(branch_iterator&&) = default;
    branch_iterator& operator=(branch_iterator&&) = default;

    ~branch_iterator();

    branch& operator*() { return m_branch; }
    branch* operator->() { return &m_branch; }
    branch_iterator& operator++();

    friend bool operator==(const branch_iterator& lhs,
                           const branch_iterator& rhs);

    friend bool operator!=(const branch_iterator& lhs,
                           const branch_iterator& rhs);

  private:
    git_branch_iterator* m_iter = nullptr;
    branch m_branch;
  };

  branch_iterator branch_begin(git_branch_t list_flags) const;
  branch_iterator branch_end() const;

private:
  std::unique_ptr<git_repository, std::function<void(git_repository*)>> m_repo;
};

}  // namespace git2wrap

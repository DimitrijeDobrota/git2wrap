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

}  // namespace git2wrap

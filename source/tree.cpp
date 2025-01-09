#include "git2wrap/tree.hpp"

#include "git2wrap/error.hpp"
#include "git2wrap/object.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

tree::tree(git_tree* tre, repositoryPtr repo)
    : m_tree(tre, git_tree_free)
    , m_repo(std::move(repo))
{
}

tree tree::dup() const
{
  git_tree* tre = nullptr;

  if (auto err = git_tree_dup(&tre, m_tree.get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return {tre, m_repo};
}

const oid* tree::get_id() const
{
  return git_tree_id(m_tree.get());
}

repositoryPtr tree::get_owner() const
{
  return m_repo;
}

size_t tree::get_entrycount() const
{
  return git_tree_entrycount(m_tree.get());
}

tree_entry tree::get_entry(const char* name) const
{
  return {git_tree_entry_byname(m_tree.get(), name), m_repo};
}

tree_entry tree::get_entry(size_t idx) const
{
  return {git_tree_entry_byindex(m_tree.get(), idx), m_repo};
}

tree_entry tree::get_entry(const oid* objid) const
{
  return {git_tree_entry_byid(m_tree.get(), objid), m_repo};
}

tree_entry tree::get_entry_path(const char* path) const
{
  git_tree_entry* entry = nullptr;

  if (auto err = git_tree_entry_bypath(&entry, m_tree.get(), path)) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return {entry, m_repo};
}

tree_entry::tree_entry(const git_tree_entry* entry, repositoryPtr repo)
    : m_entry(const_cast<git_tree_entry*>(entry), empty_lambda)  // NOLINT
    , m_repo(std::move(repo))
{
}

tree_entry::tree_entry(git_tree_entry* entry, repositoryPtr repo)
    : m_entry(entry, git_tree_entry_free)
    , m_repo(std::move(repo))
{
}

tree_entry tree_entry::dup() const
{
  git_tree_entry* entry = nullptr;

  if (auto err = git_tree_entry_dup(&entry, m_entry.get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return {entry, m_repo};
}

object tree_entry::to_object() const
{
  git_object* obj = nullptr;

  if (auto err = git_tree_entry_to_object(&obj, m_repo.get(), m_entry.get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return {obj, m_repo};
}

tree tree_entry::to_tree() const
{
  git_object* obj = nullptr;

  if (auto err = git_tree_entry_to_object(&obj, m_repo.get(), m_entry.get())) {
    throw error(err, git_error_last(), __FILE__, __LINE__);
  }

  return {reinterpret_cast<git_tree*>(obj), m_repo};  // NOLINT
}

const char* tree_entry::get_name() const
{
  return git_tree_entry_name(m_entry.get());
}

const oid* tree_entry::get_id() const
{
  return git_tree_entry_id(m_entry.get());
}

object_t tree_entry::get_type() const
{
  return git_tree_entry_type(m_entry.get());
}

filemode_t tree_entry::get_filemode() const
{
  return git_tree_entry_filemode(m_entry.get());
}

filemode_t tree_entry::get_filemode_raw() const
{
  return git_tree_entry_filemode_raw(m_entry.get());
}

auto tree_entry::operator<=>(const tree_entry& rhs)
{
  return git_tree_entry_cmp(m_entry.get(), rhs.m_entry.get());
}

}  // namespace git2wrap

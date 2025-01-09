#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT tree
{
public:
  tree(git_tree* tre, repositoryPtr repo);

  operator bool() const { return m_tree != nullptr; }  // NOLINT
  tree dup() const;

  const oid* get_id() const;
  repositoryPtr get_owner() const;
  size_t get_entrycount() const;

  tree_entry get_entry(const char* name) const;
  tree_entry get_entry(size_t idx) const;
  tree_entry get_entry(const oid* objid) const;
  tree_entry get_entry_path(const char* path) const;

private:
  treeUPtr m_tree;
  repositoryPtr m_repo;
};

class GIT2WRAP_EXPORT tree_entry
{
public:
  tree_entry(const git_tree_entry* entry, repositoryPtr repo);
  tree_entry(git_tree_entry* entry, repositoryPtr repo);

  operator bool() const { return m_entry != nullptr; }  // NOLINT
  tree_entry dup() const;

  object to_object() const;
  tree to_tree() const;

  const char* get_name() const;
  const oid* get_id() const;
  object_t get_type() const;
  filemode_t get_filemode() const;
  filemode_t get_filemode_raw() const;

  auto operator<=>(const tree_entry& rhs);

private:
  tree_entryPtr m_entry;
  repositoryPtr m_repo;
};

}  // namespace git2wrap

#pragma once

#include <git2.h>

#include "git2wrap/git2wrap_export.hpp"
#include "git2wrap/oid.hpp"
#include "git2wrap/types.hpp"

namespace git2wrap
{

class GIT2WRAP_EXPORT tree
{
public:
  tree(git_tree* tre, repositoryPtr repo);

  operator bool() const { return m_tree != nullptr; }  // NOLINT
  [[nodiscard]] git_tree* ptr() const { return m_tree.get(); }
  [[nodiscard]] tree dup() const;

  [[nodiscard]] oid get_id() const;
  [[nodiscard]] repositoryPtr get_owner() const;
  [[nodiscard]] size_t get_entrycount() const;

  [[nodiscard]] tree_entry get_entry(const char* name) const;
  [[nodiscard]] tree_entry get_entry(size_t idx) const;
  [[nodiscard]] tree_entry get_entry(const oid& objid) const;
  [[nodiscard]] tree_entry get_entry_path(const char* path) const;

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
  [[nodiscard]] tree_entry dup() const;

  [[nodiscard]] object to_object() const;
  [[nodiscard]] tree to_tree() const;

  [[nodiscard]] const char* get_name() const;
  [[nodiscard]] repositoryPtr get_owner() const;
  [[nodiscard]] oid get_id() const;
  [[nodiscard]] object_t get_type() const;
  [[nodiscard]] filemode_t get_filemode() const;
  [[nodiscard]] filemode_t get_filemode_raw() const;

  auto operator<=>(const tree_entry& rhs);

private:
  tree_entryPtr m_entry;
  repositoryPtr m_repo;
};

}  // namespace git2wrap

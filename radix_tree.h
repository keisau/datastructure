#ifndef __DS_RADIX_TREE_H__
#define __DS_RADIX_TREE_H__

#include "class.h"
#include "list.h"

enum {
	E_NO_ERROR = 0,
	E_EXIST,
	E_NOT_FOUND,
};

/**
 * radix tree 
 */
struct radix_tree {
	unsigned long		size;
	struct radix_node	*root;
	struct list_head	head;
};

struct radix_data_node {
	unsigned long		key;
	void				*data;
	struct list_head	iter_head;
};

#define rt_dnode(ptr) (container_of (ptr, struct radix_data_node, head))

extern class radix_tree;
void * radix_tree_insert (struct radix_tree *tree, unsigned long key, void *data);
struct radix_data_node * radix_tree_find (struct radix_tree *tree, unsigned long key);
void * radix_tree_delete (struct radix_tree *tree, unsigned long key);
void radix_tree_dump (struct radix_tree *tree);

#endif // __DS_RADIX_TREE_H__

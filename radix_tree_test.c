#include <stdio.h>
#include "radix_tree.h"

int main () {
	struct radix_tree *tree = radix_tree.new ();
	int i, tmp;
	if (tree) {
		struct list_head *iter = tree->head.next;
		struct list_head *head = NULL;
		struct radix_data_node *dnode = NULL;
		if (iter == &tree->head)
			puts ("Nothing inside");

		radix_tree_insert (tree, 0x12345678, (void*) 0x87654321);
		radix_tree_insert (tree, 0x12345600, (void*) 0x654321);
		radix_tree_insert (tree, 0x12, (void*) 0x1234321);
		radix_tree_dump (tree);
		dnode = radix_tree_find (tree, 0x12345678);
		if (dnode == NULL) {
			puts ("not found");
		} else {
			printf ("key : 0x%lx\n", dnode->key);
			printf ("data : %p\n", dnode->data);
		}
		puts ("--------small number test----------");
		dnode = radix_tree_find (tree, 0x12);
		if (dnode == NULL) {
			puts ("not found");
		} else {
			printf ("key : 0x%lx\n", dnode->key);
			printf ("data : %p\n", dnode->data);
		}
		dnode = radix_tree_find (tree, 0x13);
		if (dnode == NULL) {
			puts ("not found");
		} else {
			printf ("key : 0x%lx\n", dnode->key);
			printf ("data : %p\n", dnode->data);
		}
		puts ("---------delete test----------");
		radix_tree_delete (tree, 0x12345678);
		radix_tree_delete (tree, 0x12345600);
		radix_tree_dump (tree);
		radix_tree.delete (tree);

		puts ("---------memory test----------");
		/*
		for (i = 0; i < 256; ++i) {
			int j;
			printf ("pass %d\n", i);
			tree = radix_tree.new ();
			for (j = 0; j < 1 << 18; ++j)
				radix_tree_insert (tree, j, (void*) j);
			radix_tree.delete (tree);
		}
		*/
		puts ("See memory usage");
		for (i = 0; i < 256; ++i) {
			int j;
			printf ("pass %d\n", i);
			tree = radix_tree.new ();
			for (j = 0; j < 1 << 18; ++j)
				radix_tree_insert (tree, j, (void*) (long)j);
			for (j = 0; j < 1 << 18; ++j)
				radix_tree_delete (tree, j);
		}
	}
	return 0;
}

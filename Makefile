all: radix_tree hash

radix_tree:
	cc -c radix_tree.c
	cc -c radix_tree_test.c
	cc radix_tree.o radix_tree_test.o -o radix_tree_test

hash:
	cc -c hash.c

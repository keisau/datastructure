CC		:= gcc
LD		:= gcc

all: radix_tree hash

radix_tree:
	$(CC) -c radix_tree.c
	$(CC) -c radix_tree_test.c
	$(LD) radix_tree.o radix_tree_test.o -o radix_tree_test

hash:
	$(CC) -c hash.c

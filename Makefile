RADIX_TREE_OBJ				:= radix_tree.o \
							radix_tree_test.o

HASH_OBJ					:= hash.o

CC		:= gcc
LD		:= gcc

all: radix_tree

radix_tree: $(RADIX_TREE_OBJ)
	$(LD) $(RADIX_TREE_OBJ) -o radix_tree_test

%.o: %.c
	$(CC) $< -o $@

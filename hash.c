#include "hash.h"
#include "list.h"

struct hash_data_node {
	void *key;
	void *data;
	struct list_head iter_head;
};

struct hash_table {
	void *h_table;

};

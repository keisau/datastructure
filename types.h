#ifndef __DS_TYPES_H__
#define __DS_TYPES_H__

struct list_head {
	struct list_head *next, *prev;
};

struct hlist_head {
	struct hlist_node *first;
};

struct hlist_node {
	struct hlist_node *next, **pprev;
};
#endif // __DS_TYPES_H__

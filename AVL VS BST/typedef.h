#ifndef typedef
#define typedef

typedef struct binary_t binary_tree;
struct binary_t
{
	int item;
	struct binary_t *left;
	struct binary_t *right;
};

#endif
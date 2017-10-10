#include <stdlib.h>
#include "simple_logger.h"

typedef struct btreenode_s
{
	void * data;
	struct btreenode_s * left_child;
	struct btreenode_s * right_child;
	size_t elementSize;
}BinaryTreeNode;

BinaryTreeNode * bt_new(size_t elementSize);
void * bt_delete(BinaryTreeNode ** node);
int bt_insert(BinaryTreeNode ** root, void * data, size_t elementSize);
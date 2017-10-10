#include "ds_binary_tree.h"

int bt_free_node(BinaryTreeNode * node)
{
	if (!node)
	{
		slog("Error: trying to free a bi tree node that is already NULL");
		return -2;
	}
	if (node->data != NULL)
	{
		slog("Error: trying to free a bi tree node that still has data in it");
		return -1;
	}
	free(node);
	return 0;
}

BinaryTreeNode * bt_new(size_t elementSize)
{
	BinaryTreeNode * node;
	node = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode) + elementSize);
	if (node == NULL)
	{
		slog("Error: could not allocate memory for a new BinaryTreeNode");
		return NULL;
	}
	memset(node, 0, sizeof(BinaryTreeNode) + elementSize);
	node->elementSize = elementSize;
	return node;
}

void * bt_delete(BinaryTreeNode ** node)
{
	return NULL;
}

int bt_insert(BinaryTreeNode ** root, void * data, size_t elementSize)
{
	BinaryTreeNode * new_node = bt_new(elementSize);
	BinaryTreeNode * iterator = (*root);
	if (!new_node)
	{
		return -1;
	}
	new_node->data = data;

	if ((*root) == NULL)
	{
		(*root) == new_node;
	}
	else
	{
		while (iterator != NULL)
		{
			
		}
	}

	return 0;
}

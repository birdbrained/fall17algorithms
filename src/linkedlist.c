#include <SDL.h>
#include "linkedlist.h"
#include "simple_logger.h"

LL_Node * linkedlist_new_node()
{
	LL_Node *node;
	node = (LL_Node *)malloc(sizeof(LL_Node));
	if (!node)
	{
		slog("bad");
		return NULL;
	}
	memset(node, 0, sizeof(LL_Node));
}

int linkedlist_free_node(LL_Node *node)
{
	if (!node)
	{
		slog("Error: trying to free node that is already NULL");
		return -2;
	}
	if (node->data != NULL)
	{
		slog("Error: data still present in node");
		return -1;
	}
	free(node);
	return 0;
}

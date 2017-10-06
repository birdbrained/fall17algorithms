#include "ds_graph.h"

GraphNode * graph_new(size_t elementSize)
{
	GraphNode * node;
	node = (GraphNode *)malloc(sizeof(GraphNode) + elementSize);
	if (node == NULL)
	{
		slog("Error: could not allocate memory for a new graph node");
		return NULL;
	}
	memset(node, 0, sizeof(GraphNode) + elementSize);
	node->elementSize = elementSize;
	return node;
}

int graph_insert(GraphNode ** start, void * data, size_t elementSize, int width)
{
	GraphNode * node = graph_new(elementSize);
	GraphNode * temp = node;
	if (node == NULL)
	{
		return -1;
	}

	node->data = data;
	node->elementSize = elementSize;

	//if the node is the first one to be added
	if ((*start) == NULL)
	{
		(*start) = node;
	}
	//otherwise, gotta add shit on
	else
	{

	}

	return 0;
}

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

Graph * graph_init(int width, size_t elementSize)
{
	int i = 0;
	Graph * grape;
	grape = (Graph *)malloc(sizeof(Graph));
	if (grape == NULL)
	{
		slog("Error: could not allocate memory for a new graph");
		return NULL;
	}
	memset(grape, 0, sizeof(Graph));
	grape->head = graph_new(elementSize);
	grape->tail = graph_new(elementSize);
	grape->width = width;
	for (i = 0; i < width; i++)
	{
		grape->prevRow[i] = (GraphNode *)malloc(sizeof(GraphNode));
		if (grape->prevRow[i] == NULL)
		{
			slog("Error: could not allocate memory for prevRow[%i]", i);
			return NULL;
		}
	}
	return grape;
}

int graph_insert(Graph ** graph, void * data, int width, size_t elementSize)
{
	GraphNode * node = graph_new(elementSize);
	GraphNode * temp = NULL;
	//GraphNode * temp = node;
	if (node == NULL)
	{
		return -1;
	}

	node->data = data;
	node->elementSize = elementSize;

	//if the node is the first one to be added
	if ((*graph)->head == NULL)
	{
		(*graph)->head = node;
		(*graph)->tail = node;
		(*graph)->head->x = 0;
		(*graph)->head->y = 0;
	}
	//otherwise, gotta add shit on
	else
	{
		if ((*graph)->tail->x + 1 < width)		//if x + 1 < width...
		{
			node->x = (*graph)->tail->x + 1;	//new node has x++
			node->y = (*graph)->tail->y;		//new node's y is still the same
			(*graph)->tail->right_node = node;	//iterator's right = new node
			node->left_node = (*graph)->tail;	//new node's left = iterator
			(*graph)->tail = node;				//iterator = new node

			/*if ((*graph)->prevRow[node->x] != NULL) //check if reference[x] exists, otherwise we are making first row
			{
				(*graph)->prevRow[node->x]->down_node = node;	//reference[x]'s bottom = new node
				node->up_node = (*graph)->prevRow[node->x];		//new node's top = reference[x]
			}
			(*graph)->prevRow[node->x] = node;	//make reference[x] = new node
			if (prevRow[node->x] != NULL)
			{
				prevRow[node->x]->down_node = node;
				node->up_node = prevRow[node->x];
			}
			prevRow[node->x] = node;*/

			if (node->y != 0)
			{
				temp = (*graph)->head;
				while (temp->y < node->y - 1)
				{
					temp = temp->down_node;
				}
				while (temp->x < node->x)
				{
					temp = temp->right_node;
				}
				temp->down_node = node;
				node->up_node = temp;
			}
		}
		else //now it's time to move to the next row
		{
			node->x = 0;						//new node has x = 0
			(*graph)->tail = (*graph)->head;	//set iterator = start
			while ((*graph)->tail->down_node != NULL) //go down until next down pointer is NULL
			{
				(*graph)->tail = (*graph)->tail->down_node;
			}
			node->y = (*graph)->tail->y + 1;	//new node has y++
			(*graph)->tail->down_node = node;	//iterator's bottom = new node
			node->up_node = (*graph)->tail;		//new node's top = iterator
			(*graph)->tail = node;				//iterator = new node
			//prevRow[0] = node; //make reference[0] = new node
		}
	}

	return 0;
}

void graph_print(Graph ** graph)
{
	GraphNode * hor_iter = (*graph)->head;
	GraphNode * ver_iter = (*graph)->head;

	while (ver_iter != NULL)
	{
		while (hor_iter != NULL)
		{
			slog("x: (%i), y: (%i), data: (%d)", hor_iter->x, hor_iter->y, hor_iter->data);
			hor_iter = hor_iter->right_node;
		}
		ver_iter = ver_iter->down_node;
		hor_iter = ver_iter;
	}
}

void graph_print_squiggle(Graph ** graph, int numIterations)
{
	GraphNode * iter = (*graph)->head;
	int i = 0;

	if (iter == NULL)
	{
		slog("cant squiggle :(");
		return;
	}
	slog("====SQUIGGLE====");
	slog("x: (%i), y : (%i), data : (%d)", iter->x, iter->y, iter->data);
	for (i = 0; i < numIterations; i++)
	{
		if (i % 2 == 1)
		{
			iter = iter->right_node;
		}
		else
		{
			iter = iter->down_node;
		}
		if (iter == NULL)
		{
			slog("squiggle stopped early");
			return;
		}
		slog("x: (%i), y : (%i), data : (%d)", iter->x, iter->y, iter->data);
	}
	
}

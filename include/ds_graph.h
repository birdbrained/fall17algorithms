#ifndef __DS_GRAPH__
#define __DS_GRAPH__

#include <stdlib.h>
#include "simple_logger.h"

/**
 * @brief A graph node data type
 */
typedef struct graphnode_s
{
	void *data;							/**<data the node holds*/
	int x;								/**<x position in graph (left-right)*/
	int y;								/**<y position in graph (top-bottom)*/
	struct graphnode_s * up_node;		/**<These represent the nodes next to the node like a tilesheet*/
	struct graphnode_s * right_node;
	struct graphnode_s * down_node;
	struct graphnode_s * left_node;
	size_t elementSize;					/**<size of the data*/
}GraphNode;

/**
 * @brief Creates a new graph node
 * @param elementSize Size of the data to hold
 * @returns Pointer to new GraphNode; NULL if could not allocate memory
 */
GraphNode * graph_new(size_t elementSize);
int graph_insert(GraphNode ** start, void * data, size_t elementSize, int width);

#endif // !__DS_GRAPH__
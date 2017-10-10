#ifndef __DS_GRAPH__
#define __DS_GRAPH__

#define MAX_WIDTH 100

#include <stdlib.h>
#include "simple_logger.h"
#include "dj_tilemap.h"

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

typedef struct graph_s
{
	GraphNode * head;					/**<pointer to start of graph*/
	GraphNode * tail;					/**<pointer to most recently added node, aka the end*/
	int width;							/**<how wide a row should be before moving to the next*/
	GraphNode * prevRow[MAX_WIDTH];		/**<used for linking up and down node pointers*/
}Graph;

/**
 * @brief Creates a new graph node
 * @param elementSize Size of the data to hold
 * @returns Pointer to new GraphNode; NULL if could not allocate memory
 */
GraphNode * graph_new(size_t elementSize);

/**
* @brief Initializes a new graph
* @param width Max number of nodes in a single row
* @param elementSize Size of data each node will hold
* @returns Pointer to new Graph; NULL if could not allocate memory
*/
Graph * graph_init(int width, size_t elementSize);

/**
 * @brief Deletes a node from a graph, and re-assigns pointers to connect holes in graph
 * @param node The node that will be deleted
 * @returns The data the node holds; NULL if node is null
 */
void * graph_delete(GraphNode ** node);

/**
 * @brief Inserts a new graph node into the graph
 * @param graph The graph to insert into
 * @param data The data to insert
 * @param elementSize Size of data the node will hold
 * @returns -1 if could not allocate memory; 0 if successful
 */
int graph_insert(Graph ** graph, void * data, int width, size_t elementSize);

Graph * graph_load_from_tilemap(TileMap * tilemap, size_t elementSize);

/**
 * @brief Simple slog of data in graph
 * @param graph The graph to print data from
 */
void graph_print(Graph ** graph);

/**
 * @brief Print function just to test if pointers are good
 * @param graph The graph tp print data from
 * @param numIterations Number of steps to take
 */
void graph_print_squiggle(Graph ** graph, int numIterations);

#endif // !__DS_GRAPH__
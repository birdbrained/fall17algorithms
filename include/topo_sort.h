#ifndef __TOPO_SORT__
#define __TOPO_SORT__

#include "linkedlist.h"
#include "simple_logger.h"

typedef struct vertgraph_s
{
	int numVertices;
	LL_Node * adjacencyList;
}VertGraph;

VertGraph * vert_graph_init(int numVertices);
void topo_sort_through_neighbors(int numVertices);

#endif // !__TOPO_SORT__

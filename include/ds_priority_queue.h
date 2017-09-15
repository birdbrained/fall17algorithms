#ifndef __DS_PRIORITY_QUEUE__
#define __DS_PRIORITY_QUEUE__

/*
typedef struct node {
	void * data;
	int priority;
	struct node * prev;
	struct node * next;
}Node;

Node * pqInit(void * data, int priority);
void pqEnqueue(Node * pq, void * data, int priority);
Node * pqDequeue(Node * pq);
*/

#include <SDL.h>

/**
 * @brief A priority queue data structure
 */
typedef struct priorityqueue
{
	void *data;
	int priority;
	struct priorityqueue * next;
	struct priorityqueue * prev;
	size_t elementSize;
}PriorityQueue;

/**
 * @brief Creates a new priority queue
 * @param elementSize
 */
PriorityQueue *pq_new(size_t elementSize);
void *pq_delete(PriorityQueue *pq);
void *pq_delete_max(PriorityQueue *pq);

/**
 * @brief Inserts a new node into the priority queue passed into the function
 * @param pq_head The head node that will have a node inserted into it
 * @param pq_tail The tail node, required if inserting first node
 * @param data The data that will be inserted
 * @param elementSize Size of the data
 * @param priority The data's priority, larger numbers have greater priority
 * @returns 0 if successful, -1 if data could not be allocated
 */
int pq_insert(PriorityQueue ** pq_head, PriorityQueue ** pq_tail, void *data, size_t elementSize, int priority);

#endif // !__DS_PRIORITY_QUEUE__

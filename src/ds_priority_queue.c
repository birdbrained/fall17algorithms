/*
#include <SDL.h>
#include "ds_priority_queue.h"

Node * head = NULL;

Node * pqInit(void * data, int priority)
{
	Node * n = NULL;
	n = malloc(sizeof(Node));
	n->data = data;
	n->priority = priority;
	n->prev = NULL;
	n->next = NULL;
	return n;
}

void pqEnqueue(Node * pq, void * data, int priority)
{
	int i = 0;
	Node *newNode = pqInit(data, priority);

	while (pq[i].next != NULL)
	{
		i++;
	}

	newNode->prev = &pq[i];
	pq[i].next = newNode;
}

Node * pqDequeue(Node * pq)
{
	Node * n;
	int currMaxPriority = -1;
	int i = 0;

	while (pq[i] != NULL)
	{

	}

	return NULL;
}
*/

#include <SDL.h>
#include "ds_priority_queue.h"

PriorityQueue * pq_new(size_t elementSize)
{
	/*PriorityQueue *head = NULL;
	head = malloc(sizeof(PriorityQueue) + elementSize);
	head->elementSize = elementSize;
	head->numElements = 0;
	head->priority = 0;
	return head;*/

	int i;
	PriorityQueue *pq;
	pq = malloc(sizeof(PriorityQueue));
	pq->data = NULL;
	pq->elementSize = elementSize;
	pq->next = NULL;
	pq->prev = NULL;
	pq->priority = 0;
	return pq;
}

void pq_delete(PriorityQueue *pq)
{
	return NULL;
}

void *pq_delete_max(PriorityQueue *pq)
{
	int currentMaxPriority, currentMaxIndex, i;
	currentMaxPriority = -1;
	currentMaxIndex = 0;
	i = 0;

	while (pq[i].data != NULL)
	{
		if (pq[i].priority > currentMaxPriority)
		{
			currentMaxPriority = pq[i].priority;
			currentMaxIndex = i;
		}
		i++;
	}
}

void pq_insert(PriorityQueue *pq, void *data, int priority)
{
	//If the priority queue doesn't have anything in it yet
	if (pq->data == NULL)
	{

	}
}
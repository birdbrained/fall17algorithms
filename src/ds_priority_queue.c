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
#include "simple_logger.h"

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
	pq = (PriorityQueue *)malloc(sizeof(PriorityQueue) + elementSize);
	if (pq == NULL)
	{
		slog("Error: could not allocate memory for new pq node");
		return NULL;
	}
	memset(pq, 0, sizeof(PriorityQueue) + elementSize);
	pq->elementSize = elementSize;
	return pq;
}

void * pq_delete(PriorityQueue ** pq_head, PriorityQueue ** pq_tail)
{
	PriorityQueue * temp = NULL;

	temp = (*pq_tail);
	(*pq_tail) = (*pq_tail)->next;
	(*pq_tail)->prev = NULL;
	temp->next = NULL;

	return temp->data;
}

void * pq_delete_max(PriorityQueue ** pq_head)
{
	PriorityQueue * maxPriorityNode = NULL;


}

int pq_insert(PriorityQueue ** pq_head, PriorityQueue ** pq_tail, void *data, size_t elementSize, int priority)
{
	PriorityQueue * n = pq_new(elementSize);

	if (n == NULL)
	{
		return -1;
	}
	n->data = data;
	n->elementSize = elementSize;
	n->priority = priority;

	//If the priority queue doesn't have anything in it yet
	if ((*pq_head)->data == NULL)
	{
		(*pq_head) = n;
		(*pq_tail) = n;
	}
	//But if it already does, enqueue something and change the head pointer to new node
	else
	{
		n->prev = (*pq_head);
		(*pq_head)->next = n;
		(*pq_head) = n;
	}
	return 0;
}
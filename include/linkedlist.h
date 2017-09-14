#ifndef __LINKEDLIST__
#define __LINKEDLIST__

typedef struct Node_S
{
	void *data;
	struct Node_S *next;
}LL_Node;

LL_Node * linkedlist_new_node();
void linkedlist_insert(LL_Node ** head, void * data);
LL_Node * linkedlist_remove_front(LL_Node ** head);
LL_Node * linkedlist_remove_back(LL_Node ** head);
int linkedlist_free_node(LL_Node *node);

#endif // !__LINKEDLIST__

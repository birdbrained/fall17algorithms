#include "ds_spatial_hash.h"

static Hashmap * Buckets = NULL;
static int SpaceWidth = 0;
static int SpaceHeight = 0;
static int CellSize = 0;
static int TotalCells = 0;

void spatial_setup(int spaceWidth, int spaceHeight, int cellSize, size_t elementSize)
{
	int numColumns = spaceWidth / cellSize;
	int numRows = spaceHeight / cellSize;
	int totalCells = numColumns * numRows;
	int i = 0;

	Buckets = hashmap_init(totalCells);

	for (i = 0; i < totalCells; i++)
	{
		hashmap_insert(&Buckets, (char)i, NULL, sizeof(LL_Node) + elementSize);
	}

	SpaceWidth = spaceWidth;
	SpaceHeight = spaceHeight;
	CellSize = cellSize;
	TotalCells = totalCells;
}

void spatial_clear()
{
	int i = 0;
	void * data = NULL;

	for (i = 0; i < TotalCells; i++)
	{
		data = hashmap_get_data(Buckets, (char)i); 
		while (data != NULL)
		{
			linkedlist_free_node(linkedlist_remove_front(data));
		}
	}
}

void spatial_register_body(Body * body)
{
	LL_Node * cellIDs = spatial_body_in_buckets(body);
	LL_Node * iterator = cellIDs;

	while (iterator != NULL)
	{
		linkedlist_insert(hashmap_get_data(Buckets, (char)iterator->data), body, sizeof(Body));
	}
}

LL_Node * spatial_body_in_buckets(Body * body)
{
	LL_Node * ll = NULL;
	Vector2D min = vector2d(0, 0);
	Vector2D max = vector2d(0, 0);
	
	switch (body->shape->type) 
	{
	case ST_RECT:
		min.x = body->position.x - (body->shape->s.r.w / 2);
		break;
	case ST_CIRCLE:
		break;
	default:
		break;
	}
	body->shape->s.r.x;

	return NULL;
}

void spatial_add_buckets(Vector2D position, float width, LL_Node bucket)
{
}

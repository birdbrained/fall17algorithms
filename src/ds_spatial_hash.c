#include "ds_spatial_hash.h"

static Hashmap * Buckets = NULL;
static int SpaceWidth = 0;
static int SpaceHeight = 0;
static int CellSize = 0;
static int TotalCells = 0;

Hashmap * spatial_setup(int spaceWidth, int spaceHeight, int cellSize, size_t elementSize)
{
	int numColumns = spaceWidth / cellSize;
	int numRows = spaceHeight / cellSize;
	int totalCells = numColumns * numRows;
	int i = 0;
	Hashmap * hash = NULL;
	char key[16] = "";

	//Buckets = hashmap_init(totalCells);
	hash = hashmap_init(totalCells);

	if (!hash)
	{
		//slog in hashmap_init
		return NULL;
	}

	for (i = 0; i < totalCells; i++)
	{
		//hashmap_insert(&Buckets, (char)i, NULL, sizeof(LL_Node) + elementSize);
		sprintf(key, "%d", i);
		hashmap_insert(&hash, key, NULL, sizeof(LL_Node) + elementSize);
	}

	SpaceWidth = spaceWidth;
	SpaceHeight = spaceHeight;
	CellSize = cellSize;
	TotalCells = totalCells;

	return hash;
}

void spatial_clear(Hashmap ** hash)
{
	int i = 0;
	void * data = NULL;
	char * key = "";

	for (i = 0; i < TotalCells; i++)
	{
		//data = hashmap_get_data(Buckets, (char)i); 
		sprintf(key, "%d", i);
		data = hashmap_get_data((*hash), key);
		while (data != NULL)
		{
			linkedlist_free_node(linkedlist_remove_front(data));
		}
	}
}

void spatial_register_body(Hashmap ** hashmap, Body * body)
{
	LL_Node * cellIDs = spatial_body_in_buckets(body);	//Should be a list of all the cells the body is in
	LL_Node * iterator = cellIDs;						//To iterate through linked list

	while (iterator != NULL)
	{
		//linkedlist_insert(hashmap_get_data(Buckets, (char)iterator->data), body, sizeof(Body));
		linkedlist_insert(hashmap_get_data(hashmap, (char)iterator->data), body, sizeof(Body));
		iterator = iterator->next;
	}

	//clean up
	while (cellIDs != NULL)
	{
		linkedlist_remove_front(&cellIDs);
	}
}

LL_Node * spatial_body_in_buckets(Body * body)
{
	LL_Node * ll = NULL;
	Vector2D min = vector2d(0, 0);
	Vector2D max = vector2d(0, 0);
	float width = 0.0f;
	
	switch (body->shape->type) //determine the boundaries to check where a body is
	{
	case ST_RECT:
		min.x = body->position.x - (body->shape->s.r.w / 2);
		min.y = body->position.y - (body->shape->s.r.h / 2);
		max.x = body->position.x + (body->shape->s.r.w / 2);
		max.y = body->position.y + (body->shape->s.r.h / 2);
		break;
	case ST_CIRCLE:
		min.x = body->position.x - body->shape->s.c.r;
		min.y = body->position.y - body->shape->s.c.r;
		max.x = body->position.x + body->shape->s.c.r;
		max.y = body->position.y + body->shape->s.c.r;
		break;
	default:
		break;
	}
	width = SpaceWidth / CellSize;

	//check each corner and add each corner to the bucket/grid space it's on
	//top left
	spatial_add_buckets(min, width, body->id, &ll);
	//top right
	spatial_add_buckets(vector2d(max.x, min.y), width, body->id, &ll);
	//bottom left
	spatial_add_buckets(vector2d(min.x, max.y), width, body->id, &ll);
	//bottom right
	spatial_add_buckets(max, width, body->id, &ll);

	return ll;
}

void spatial_add_buckets(Vector2D position, float width, /*Uint8 bodyID,*/ LL_Node ** bucket)
{
	//LL_Node ** bucket holds numbers corresponding to which cell(s) a body is in
	int cellNum = 0;
	Uint8 bodyAlreadyInBucket = 0;
	LL_Node * iterator = NULL;
	
	cellNum = (int)(floor(position.x / CellSize) + floor(position.y / CellSize) * width);	//the id of the one point in a cell
	iterator = (*bucket);

	while (iterator != NULL)
	{
		if ((int)iterator->data == cellNum)  //if the same id has already been accounted for...dont add it again
		{
			bodyAlreadyInBucket = 1;
			break;
		}
		iterator = iterator->next;
	}

	if (!bodyAlreadyInBucket)
	{
		linkedlist_insert(bucket, cellNum, sizeof(int));
	}
}

void spatial_update(Space * space, Hashmap ** hashmap)
{
	int numBodies = 0;
	int i = 0;
	Body * body = NULL;

	numBodies = gf2d_list_get_count(space->bodyList);

	for (i = 0; i < numBodies; i++)
	{
		body = (Body*)gf2d_list_get_nth(space->bodyList, i);
		if (!body)
		{
			continue;
		}
	}
}

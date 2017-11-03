#include "ds_hashmap.h"

/**
 * @brief Totes the bestest hash eva ~<3
 * @param str String you want to hash
 * @returns A hashed unsigned long
 */
unsigned long crappy_hash(char * str)
{
	int i = 0;
	unsigned long hash = 0;

	while (str[i] != '\0')
	{
		hash += (int)str[i];
		i++;
	}

	return hash;
}

Hashmap * hashmap_init(unsigned int maxNodes)
{
	Hashmap * hashbrown;
	hashbrown = (Hashmap *)malloc(sizeof(Hashmap));
	if (!hashbrown)
	{
		slog("Error: could not allocate memory for a new hashmap");
		return NULL;
	}
	memset(hashbrown, 0, sizeof(Hashmap));
	hashbrown->map = (HashmapNode *)malloc(sizeof(HashmapNode) * maxNodes);
	if (!hashbrown->map)
	{
		slog("Error: could not allocate memory for the hashmap's map");
		return NULL;
	}
	memset(hashbrown->map, 0, sizeof(HashmapNode) * maxNodes);
	hashbrown->maxNodes = maxNodes;
	return hashbrown;
}

HashmapNode * hashmap_new_node(size_t elementSize)
{
	HashmapNode * node;
	node = (HashmapNode *)malloc(sizeof(HashmapNode) + elementSize);
	if (!node)
	{
		slog("Error: could not allocate memory for a new hashmap node");
		return NULL;
	}
	memset(node, 0, sizeof(HashmapNode) + elementSize);
	node->elementSize = elementSize;
	return node;
}

int hashmap_insert(Hashmap ** hashbrown, char * key, void * data, size_t elementSize)
{
	unsigned long _key = crappy_hash(key);
	int index = 0;
	HashmapNode * new_node = hashmap_new_node(elementSize);

	if (!hashbrown)
	{
		slog("Error: cannot insert into a null hashmap");
		return -1;
	}
	if (!new_node)
	{
		//error slog in hashmap_new_code
		return -2;
	}

	strncpy(new_node->key, key, MAX_KEY_LENGTH);
	new_node->value = data;
	index = _key % (*hashbrown)->maxNodes;

	//if ((*hashbrown)->map[index].key == NULL)
	if (strncmp("", (*hashbrown)->map[index].key, MAX_KEY_LENGTH) == 0)
	{
		(*hashbrown)->map[index] = (*new_node);
	}

	return 0;
}

void hashmap_print(Hashmap * hashbrown)
{
	int i = 0;
	if (!hashbrown)
	{
		slog("Error: cannot print from a null hashmap");
		return;
	}
	for (i = 0; i < hashbrown->maxNodes; i++)
	{
		if (strncmp(hashbrown->map[i].key, "", MAX_KEY_LENGTH) != 0)
		{
			slog("key: (%s) value: (%d)", hashbrown->map[i].key, hashbrown->map[i].value);
		}
	}
}

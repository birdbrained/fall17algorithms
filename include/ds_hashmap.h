#ifndef __DS_HASHMAP__
#define __DS_HASHMAP__

#include <stdlib.h>
#include <string.h>
#include "simple_logger.h"

#define MAX_KEY_LENGTH 512	/**<Maximum length for the key*/

typedef struct hashmapnode_s
{
	char key[MAX_KEY_LENGTH];
	void * value;
	size_t elementSize;
}HashmapNode;

typedef struct hashmap_s
{
	HashmapNode * map;
	unsigned int maxNodes;
}Hashmap;

//unsigned long crappy_hash(char * str);

/**
 * @brief Initializes a new hashmap
 * @param maxNodes The max number of nodes for the hashmap
 * @returns A pointer to a new hashmap; NULL if could not allocate memory
 */
Hashmap * hashmap_init(unsigned int maxNodes);

/**
 * @brief Initializes a new hashmap node
 * @param elementSize The size of the element to hold
 * @returns A pointer to a new hashmap node; NULL if could not allocate memory
 */
HashmapNode * hashmap_new_node(size_t elementSize);

int hashmap_insert(Hashmap ** hashbrown, char * key, void * data, size_t elementSize);
void * hashmap_get_data(Hashmap * hashbrown, char * key);
int hashmap_delete(Hashmap ** hashbrown, char * key);
int hashmap_clear(Hashmap * hashbrown);
void hashmap_print(Hashmap * hashbrown);

#endif // !__DS_HASHMAP__

#ifndef __DS_SPATIAL_HASH__
#define __DS_SPATIAL_HASH__

#include <stdlib.h>
#include "simple_logger.h"
#include "ds_hashmap.h"
#include "linkedlist.h"
#include "gf2d_vector.h"
#include "gf2d_collision.h"

/**
 * @brief Sets up the hashmap "Buckets" that will be used to determine the spatial hash
 * @param spaceWidth The width of the entire space collisions can happen on
 * @param spaceHeight The height of the entire space collisions can happen on
 * @param cellSize The width and height each cell will be (always square shaped)
 * @param elementSize The size of the collision-enabled object
 */
void spatial_setup(int spaceWidth, int spaceHeight, int cellSize, size_t elementSize);

/**
 * @brief Clears the data from each node in the spatial hashmap
 */
void spatial_clear();

/**
 * @brief Determines the buckets a body sits in, and assigns it to those buckets
 * @param body The body is register
 */
void spatial_register_body(Body * body);

/**
 * @brief Does the determining for spatial_register_body
 * @param body The body to lookup
 * @returns A linked list of all of the buckets the body is in
 */
LL_Node * spatial_body_in_buckets(Body * body);

/**
 * @brief Adds the "buckets" into the spatial hash (areas to break collisions down into)
 * @param position
 * @param width
 * @param bucket
 */
void spatial_add_buckets(Vector2D position, float width, LL_Node bucket);

#endif // !__DS_SPATIAL_HASH__


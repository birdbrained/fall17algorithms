#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "ds_linked_list.h"
#include "ds_priority_queue.h"
#include "ds_graph.h"
#include "linkedlist.h"
#include "dj_tilemap.h"


int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
	Sprite *sprite;
	TileMap *map;
	static Vector2D path[500];
    
    int mx,my;
    float mf = 0;
    Sprite *mouse;
    Vector4D mouseColor = {255,100,255,200};

	//Assignment variables
	Graph *myGraph = graph_init(4, sizeof(int));
	//Graph *testAStar = graph_init(4, sizeof(int));
	GraphNode *start, *goal, *data;
	PriorityQueue * endingTrail_head = pq_new(sizeof(GraphNode) + sizeof(int));
	PriorityQueue * endingTrail_tail = pq_new(sizeof(GraphNode) + sizeof(int));
	int i = 0;
	Vector2D currentDrawPath = { 0, 0 };
    
    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
    SDL_ShowCursor(SDL_DISABLE);

    /*demo setup*/
    sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);

	map = tilemap_load("levels/tilemap.map");
	//vector2d_copy(path[0], map->start);
	//vector2d_copy(path[1], vector2d(10, 10));
	//vector2d_copy(path[2], map->end);

	//my stuff for assignment
	if (myGraph != NULL)
	{
		myGraph = graph_load_from_tilemap(map, sizeof(int), 1);
		start = graph_find_node(myGraph, map->start.x, map->start.y);
		goal = graph_find_node(myGraph, map->end.x, map->end.y);
		if (start != NULL && goal != NULL)
		{
			slog("reach the end? %i", graph_a_star(&start, goal, sizeof(int), endingTrail_head, endingTrail_tail));
		}
		//graph_print(myGraph);
	}
	while (endingTrail_tail != NULL && endingTrail_tail->data != NULL)
	{
		data = pq_delete(endingTrail_head, endingTrail_tail);
		currentDrawPath.x = data->x;//(data->x * map->tileset->frame_w) + (map->tileset->frame_w / 2) + map->start.x;
		currentDrawPath.y = data->y;//(data->y * map->tileset->frame_h) + (map->tileset->frame_h / 2) + map->start.y;
		vector2d_copy(path[i], currentDrawPath);
		i++;
		slog("final: x (%i), y (%i), data (%i)", data->x, data->y, data->data);
	}
	//vector2d_copy(path[i], map->end);


    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;
        
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
		//backgrounds drawn first
		gf2d_sprite_draw_image(sprite,vector2d(0,0));

		tilemap_draw(map, vector2d(86, 24));
		tilemap_draw_path(path, i, map, vector2d(86, 24));

		//UI elements last
		gf2d_sprite_draw(
			mouse,
			vector2d(mx,my),
			NULL,
			NULL,
			NULL,
			NULL,
			&mouseColor,
			(int)mf);
		gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/

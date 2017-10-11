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
	static Vector2D path[3];
    
    int mx,my;
    float mf = 0;
    Sprite *mouse;
    Vector4D mouseColor = {255,100,255,200};

	//Assignment variables
	Graph *myGraph = graph_init(4, sizeof(int));
	int i = 0;
    
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
	vector2d_copy(path[0], map->start);
	vector2d_copy(path[1], vector2d(10, 10));
	vector2d_copy(path[2], map->end);

	//my stuff for assignment
	/*if (myGraph != NULL)
	{
		for (i = 0; i < 16; i++)
		{
			graph_insert(myGraph, i, myGraph->width, sizeof(int));
		}
		graph_print(myGraph);
		//slog("down data from start (%i)", myGraph->head->down_node->data);
		//slog("width: (%i)", myGraph->width);
		graph_print_squiggle(myGraph, 7);
	}*/
	if (myGraph != NULL)
	{
		myGraph = graph_load_from_tilemap(map, sizeof(int));
		graph_print(myGraph);
	}

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
		tilemap_draw_path(path, 3, map, vector2d(86, 24));

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

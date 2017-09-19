#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "ds_linked_list.h"
#include "ds_priority_queue.h"
#include "linkedlist.h"

typedef struct
{
	int width;
}Brick;

void draw_stack(Sprite *brick, Vector2D start, Brick *bricklist, unsigned int count)
{
	unsigned int i, j;
	int brickheight = 32;
	int brickwidth = 32;
	Vector2D drawPosition;
	if (!brick)return;
	if (!bricklist)return;
	for (i = 0; i < count; i++)
	{
		//vertical draw
		drawPosition.x = start.x - ((bricklist[i].width * brickwidth) / 2);
		drawPosition.y = start.y - ((i + 1) * brickheight);
		for (j = 0;j < bricklist[i].width;j++)
		{
			//horizontal draw
			drawPosition.x += brickwidth;
			gf2d_sprite_draw(
				brick,
				drawPosition,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				0);
		}
	}
}

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *sprite, *brick;
	static Brick bricklist[] =
	{
		{2},
		{7},
		{1},
		{5},
		{14},
		{9},
		{13},
		{24},
		{16},
		{22}
	};
    
    int mx,my;
    float mf = 0;
    Sprite *mouse;
    Vector4D mouseColor = {255,100,255,200};

	//whee
	PriorityQueue *pq_head = NULL;
	PriorityQueue *pq_tail = NULL;
	int p = 0;
	//LL_Node * ll_head = NULL;
    
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
	brick = gf2d_sprite_load_all("images/brick.png",32,32,16);
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);

	//my stuff
	/*pq = pq_new(sizeof(int), 10);
	//pq_insert(pq, 5, 1);
	//pq_insert(pq, 10, 1);
	//pq_insert(pq, 7, 2);
	ll_head = linkedlist_new_node();
	linkedlist_insert(ll_head, 5);
	linkedlist_insert(ll_head, 7);
	while (ll_head->data != NULL)
	{
		slog("Popping (%i)", linkedlist_remove_back(ll_head)->data);
	}*/

	//pq!
	pq_head = pq_new(sizeof(int));
	pq_tail = pq_new(sizeof(int));
	pq_insert(pq_head, pq_tail, 5, sizeof(int), 1);
	pq_insert(pq_head, pq_tail, 6, sizeof(int), 1);
	pq_insert(pq_head, pq_tail, 7, sizeof(int), 3);
	pq_insert(pq_head, pq_tail, 9, sizeof(int), 2);
	while (pq_head != NULL)
	{
		p = pq_delete_max(pq_head, pq_tail);
		if (p == NULL)
		{
			break;
		}
		slog("Removing (%d) from pq", p);
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

			draw_stack(brick, vector2d(600, 700), bricklist, 10);
            
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

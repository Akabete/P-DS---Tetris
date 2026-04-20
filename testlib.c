#include "primlib.h"
#include "model.h"
#include "view.h"
#include "controller.h"


#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
	srand(time(NULL));
	
	
	if (gfx_init()) exit(3);

	int max_tile_height = gfx_screenHeight() / BOARD_HEIGHT;
	int max_tile_width = gfx_screenWidth() / (NEXT_BLOCK_X + 4);

	board.tile_size = (max_tile_height < max_tile_width) ? max_tile_height : max_tile_width;

	board.offset_y = (gfx_screenHeight() - BOARD_HEIGHT * board.tile_size) / 2;
	board.offset_x = (gfx_screenWidth() - (NEXT_BLOCK_X + 4) * board.tile_size) / 2; 
	
	int frame_counter = 0;
	
	board_init();
	spawn_piece(&frame_counter);

	while(!is_game_over){
		input_handler();
		update_game_state(&frame_counter);
		draw_frame();


		SDL_Delay(10);
	}

	draw_frame();

	while(true)
		if(game_over_quit()) break;
	
	return 0;
}

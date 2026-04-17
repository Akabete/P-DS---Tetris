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
	
	int min_screen_height = (gfx_screenHeight() - BOARD_OFFSET_Y) / BOARD_HEIGHT;
	int min_screen_width = (gfx_screenWidth() - BOARD_OFFSET_X) / BOARD_WIDTH;

	tile_size = (min_screen_height < min_screen_width) ? min_screen_height : min_screen_width;


	int frame_counter = 0;
	
	board_init();
	spawn_piece(&frame_counter);

	while(!is_game_over){
		gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
	
		draw_board();
		draw_walls();

		movement_handler(&frame_counter);
		draw_active_piece();
		draw_next_piece();
		
		frame_counter++;
		
		if (frame_counter >= 60){
			if (can_move(active_y + 1, active_x, active_rotation))
			active_y++;
			else{
				freeze_piece();
				clear_lines();
				spawn_piece(&frame_counter);

				if(!can_move(active_y, active_x, active_rotation)){
					is_game_over = true;
					draw_end_screen();
				}
			}

		frame_counter = 0;
		}

		gfx_updateScreen();
		SDL_Delay(10);
	}

	gfx_getkey();
	return 0;
}

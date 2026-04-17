#include "controller.h"

int horizontal_timer = 0;

void movement_handler(int *frame_counter){
    if(!is_game_over)
    {    
        int key_pressed = gfx_pollkey();

        if (horizontal_timer > 0)
            horizontal_timer--;

        if (gfx_isKeyDown(SDLK_LEFT)){
            if (horizontal_timer == 0 && can_move(active_y, active_x - 1, active_rotation)){
                active_x -= 1;
                horizontal_timer = BLOCK_HORIZONTAL_SPEED;
            }
        }
        
        else if (gfx_isKeyDown(SDLK_RIGHT)){
            if (horizontal_timer == 0 && can_move(active_y, active_x + 1, active_rotation)){
                active_x += 1;
                horizontal_timer = BLOCK_HORIZONTAL_SPEED;
            }
        }

        else horizontal_timer = 0;


        if (key_pressed == SDLK_SPACE){
            int potential_rotation = can_rotate();    
            
            if (potential_rotation != active_rotation)
                active_rotation = potential_rotation;
        }
        
        else if (key_pressed == SDLK_DOWN){
            while(can_move(active_y + 1, active_x, active_rotation))
                active_y += 1;
            *frame_counter = 60;
        }
        
        else if (key_pressed == SDLK_c){
            // Tutaj odkładanie na bok, choć tego nie ma
            // w instrukcjach, więc w razie czego odizolować
            // Żeby się dało łatwo usunąć
        }
    }
}
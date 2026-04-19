#include "controller.h"

int horizontal_timer = 0;

void horizontal_movement_handler(){
    if (horizontal_timer > 0) horizontal_timer--;

    if (gfx_isKeyDown(SDLK_LEFT) &&
        horizontal_timer == 0 &&
        can_move(active_y, active_x - 1, active_rotation)){
            active_x--;
            horizontal_timer = BLOCK_HORIZONTAL_SPEED;
        }

    else if (gfx_isKeyDown(SDLK_RIGHT) &&
            horizontal_timer == 0 &&
            can_move(active_y, active_x + 1, active_rotation)){
                active_x++;
                horizontal_timer = BLOCK_HORIZONTAL_SPEED;
            }

    else if (!gfx_isKeyDown(SDLK_LEFT) && 
        !gfx_isKeyDown(SDLK_RIGHT))
            horizontal_timer = 0;
}

void rotation_handler(){
    int potential_rotation = can_rotate();
    if (potential_rotation != active_rotation)
        active_rotation = potential_rotation;
}

void hard_drop_handler(){
    while(can_move(active_y + 1, active_x, active_rotation))
        active_y += 1;
}


void input_handler(){
    if(is_game_over) return;

    int pressed_key = gfx_pollkey();

    horizontal_movement_handler();

    if(pressed_key == SDLK_SPACE)       rotation_handler();
    else if (pressed_key == SDLK_DOWN)  hard_drop_handler();
    else if (pressed_key == SDLK_RETURN || 
        pressed_key == SDLK_ESCAPE)     running_game_quit(pressed_key);
}


int game_over_quit(){
    int pressed_key = gfx_getkey();

    if (pressed_key == SDLK_RETURN || pressed_key == SDLK_ESCAPE)
        return 1;

    return 0;
}

void running_game_quit(int pressed_key){
    exit(0);
}
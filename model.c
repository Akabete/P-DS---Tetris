#include "model.h"
#include "pieces.txt"

int board[BOARD_HEIGHT][BOARD_WIDTH]; 

int active_x, active_y, active_type, next_type = -1, active_rotation;

bool is_game_over = false;

int tile_size;

void board_init(){
    for(int y = 0; y < BOARD_HEIGHT; y++){
        for(int x = 0; x < BOARD_WIDTH; x++)
                board[y][x] = EMPTY_SPACE_VALUE;
    }
}

void spawn_piece(int *frame_counter) {
    if(next_type == -1){
        active_type = rand() % 7;
        next_type = rand() % 7;
    } 
    else{
        active_type = next_type;
        next_type = rand() % 7;
    }

    active_rotation = 0;
    active_y = 0;
    active_x = (BOARD_WIDTH / 2) - 2;
    *frame_counter = 60;
}

int can_move(int next_y, int next_x, int next_rotation){
    for(int r = 0; r < 4; r++){
        for(int c = 0; c < 4; c++){
            if (pieces[active_type][next_rotation][r][c] != 0){
                if (next_y + r >= BOARD_HEIGHT || 
                    next_x + c < 0 || 
                    next_x + c >= BOARD_WIDTH || 
    board[next_y + r][next_x + c] != EMPTY_SPACE_VALUE)
                    return 0;
            }
        }
    }
    return 1;
}

int can_rotate(){
    int tested_rotation = (active_rotation + 1) % 4;
    if(can_move(active_y, active_x, tested_rotation))
        return tested_rotation;
    return active_rotation;
}

void freeze_piece(){
    for(int r = 0; r < 4; r++){
        for(int c = 0; c < 4; c++){
            int value = pieces[active_type][active_rotation][r][c];

            if(value != 0){
                int target_x = active_x + c;
                int target_y = active_y + r;

                if(target_y >= 0 && target_y < BOARD_HEIGHT && 
                target_x >= 0 && target_x < BOARD_WIDTH)
                    board[target_y][target_x] = PUT_BLOCK_VALUE;
            }
        }
    }
}

void clear_lines(){
    for(int y = BOARD_HEIGHT - 1; y >= 0; y--){
        bool is_line_full = true;
        for(int x = 0; x < BOARD_WIDTH; x++){
            if(board[y][x] == EMPTY_SPACE_VALUE ||board[y][x] == DELETED_SPACE_VALUE){
                is_line_full = false;
                break;
            }
        }
        if (is_line_full){
            for(int x = 0; x < BOARD_WIDTH; x++){
                board[y][x] = DELETED_SPACE_VALUE;
            }
            bool has_something_moved = false;
            do{
                has_something_moved = false;
                for(int deleting_y = BOARD_HEIGHT - 1; deleting_y >= 1; deleting_y--){
                    for(int deleting_x = 0; deleting_x < BOARD_WIDTH; deleting_x++){
                        if (board[deleting_y][deleting_x] == DELETED_SPACE_VALUE && board[deleting_y - 1][deleting_x] != DELETED_SPACE_VALUE){
                            board[deleting_y][deleting_x] = board[deleting_y - 1][deleting_x];
                            board[deleting_y - 1][deleting_x] = DELETED_SPACE_VALUE;
                            has_something_moved = true;
                        }
                    }
                }
            }while(has_something_moved);
            y++;

        }
    }
    for(int y = BOARD_HEIGHT - 1; y >= 0; y--){
        for(int x = 0; x < BOARD_WIDTH; x++){
            if (board[y][x] == DELETED_SPACE_VALUE || board[y][x] == EMPTY_SPACE_VALUE){
                board[y][x] = EMPTY_SPACE_VALUE;
            }
        }
    }
}
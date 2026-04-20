#include "model.h"
#include "pieces.txt"

bool is_game_over = false;

falling_piece active_piece;
falling_piece next_piece = {.type = -1};

game_board board;

void board_init(){
    for(int y = 0; y < BOARD_HEIGHT; y++){
        for(int x = 0; x < BOARD_WIDTH; x++)
                board.grid[y][x] = EMPTY_SPACE_VALUE;
    }
}

void spawn_piece(int *frame_counter) {
    if(next_piece.type == -1){
        active_piece.type = rand() % PIECE_AMOUNT;
        next_piece.type = rand() % PIECE_AMOUNT;
    } 
    else{
        active_piece.type = next_piece.type;
        next_piece.type = rand() % PIECE_AMOUNT;
    }

    active_piece.rotation = 0;
    active_piece.y = 0;
    active_piece.x = (BOARD_WIDTH / 2) - 2;
    *frame_counter = FRAME_COUNTER_LIMIT;
}

int can_move(int next_y, int next_x, int next_rotation){
    for(int r = 0; r < PIECE_SIZE; r++){
        for(int c = 0; c < PIECE_SIZE; c++){
            if (pieces[active_piece.type][next_rotation][r][c] != 0){
                if (next_y + r >= BOARD_HEIGHT || 
                    next_x + c < 0 || 
                    next_x + c >= BOARD_WIDTH || 
    board.grid[next_y + r][next_x + c] != EMPTY_SPACE_VALUE)
                    return 0;
            }
        }
    }
    return 1;
}

int can_rotate(){
    int tested_rotation = (active_piece.rotation + 1) % ROTATION_STATES;
    if(can_move(active_piece.y, active_piece.x, tested_rotation))
        return tested_rotation;
    return active_piece.rotation;
}

void freeze_piece(){
    for(int r = 0; r < PIECE_SIZE; r++){
        for(int c = 0; c < PIECE_SIZE; c++){
            int value = pieces[active_piece.type][active_piece.rotation][r][c];

            if(value != 0){
                int target_x = active_piece.x + c;
                int target_y = active_piece.y + r;

                if(target_y >= 0 && target_y < BOARD_HEIGHT && 
                target_x >= 0 && target_x < BOARD_WIDTH)
                    board.grid[target_y][target_x] = PUT_BLOCK_VALUE;
            }
        }
    }
}

bool is_line_full(int y){
    for(int x = 0; x < BOARD_WIDTH; x++){
        if(board.grid[y][x] == EMPTY_SPACE_VALUE || board.grid[y][x] == DELETED_SPACE_VALUE){
            return false;
        }
    }
    return true;
}

void mark_line_deleted(int y){
    for(int x = 0; x < BOARD_WIDTH; x++){
        board.grid[y][x] = DELETED_SPACE_VALUE;
    }
}

void move_blocks_down(){
    bool has_something_moved;
    do{
        has_something_moved = false;
        for(int y = BOARD_HEIGHT - 1; y >= 1; y--){
            for(int x = 0; x < BOARD_WIDTH; x++){
                if(board.grid[y][x] == DELETED_SPACE_VALUE && board.grid[y - 1][x] != DELETED_SPACE_VALUE){
                    board.grid[y][x] = board.grid[y - 1][x];
                    board.grid[y - 1][x] = DELETED_SPACE_VALUE;
                    has_something_moved = true;
                }
            }
        }
    }while(has_something_moved);
}

void clean_deleted_space(){
    for(int y = BOARD_HEIGHT - 1; y >= 0; y--){
        for(int x = 0; x < BOARD_WIDTH; x++){
            if(board.grid[y][x] == DELETED_SPACE_VALUE)
                board.grid[y][x] = EMPTY_SPACE_VALUE;
        }
    }
}

void clear_lines(){
    for(int y = BOARD_HEIGHT - 1; y >= 0; y--){
        if(is_line_full(y)){
            mark_line_deleted(y);
            move_blocks_down();
            y++;            
        }
    }
    clean_deleted_space();
}

void update_game_state(int *frame_counter){
    (*frame_counter)++;

    if (*frame_counter >= FRAME_COUNTER_LIMIT){
        if (can_move(active_piece.y + 1, active_piece.x, active_piece.rotation))
            active_piece.y++;

        else{
            freeze_piece();
            clear_lines();
            spawn_piece(frame_counter);

            if (!can_move(active_piece.y, active_piece.x, active_piece.rotation))
                is_game_over = true;
        }
        *frame_counter = 0;
    }
}
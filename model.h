#ifndef MODEL_H
#define MODEL_H

#include "settings.h"
#include "primlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

extern bool is_game_over;
extern char pieces[7][4][4][4];

typedef struct {
    int grid[BOARD_HEIGHT][BOARD_WIDTH];
    int tile_size;
    int offset_x;
    int offset_y;
} game_board;

extern game_board board;

typedef struct{
    int x;
    int y;
    int type;
    int rotation;
} falling_piece;

extern falling_piece active_piece;
extern falling_piece next_piece;

void board_init();

void spawn_piece(int *frame_counter);

int can_move(int next_y, int next_x, int next_rotation);
int can_rotate();

void freeze_piece();

bool is_line_full(int y);
void mark_line_deleted(int y);
void move_blocks_down();
void clean_deleted_space();
void clear_lines();

void update_game_state(int *frame_counter);

#endif
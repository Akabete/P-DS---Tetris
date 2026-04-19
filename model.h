#ifndef MODEL_H
#define MODEL_H

#include "settings.h"
#include "primlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

extern int active_x;
extern int active_y;
extern int active_type;
extern int next_type;
extern int active_rotation;

extern int tile_size;

extern int board_offset_x;
extern int board_offset_y;

extern bool is_game_over;

extern int board[BOARD_HEIGHT][BOARD_WIDTH];
extern char pieces[7][4][4][4];

typedef struct{
    int x;
    int y;
    int type;
    int rotation;
} falling_piece;

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
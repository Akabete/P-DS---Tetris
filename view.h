#ifndef VIEW_H
#define VIEW_H

#include "primlib.h"
#include "settings.h"
#include "model.h"

int get_board_color(int value);
void draw_board();
void draw_walls();
void draw_active_piece();
void draw_next_piece();
void draw_tile(int x, int y, int color);
void draw_end_screen();

void draw_frame();

#endif
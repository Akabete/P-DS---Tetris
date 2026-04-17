#include "view.h"

int get_board_color(int value){
    switch (value) {
        case WALL_VALUE:         return YELLOW;
        case PIECE_CENTER_VALUE: return YELLOW;
        case PIECE_BLOCK_VALUE:  return GREEN;
        case PUT_BLOCK_VALUE:    return RED;
        default:                 return BLACK;
    }
}

void draw_tile(int x, int y, int color){
    int x1 = BOARD_OFFSET_X + (x * tile_size);
    int y1 = BOARD_OFFSET_Y + (y * tile_size);

    int x2 = x1 + tile_size;
    int y2 = y1 + tile_size;

    gfx_filledRect(x1, y1, x2, y2, color);
}

void draw_walls(){
    int left_top_x = BOARD_OFFSET_X;
    int left_bottom_x = left_top_x;
    int left_top_y = BOARD_OFFSET_Y;
    int left_bottom_y = left_top_y + (BOARD_HEIGHT * tile_size);
    gfx_line(left_top_x, left_top_y, left_bottom_x, left_bottom_y, get_board_color(WALL_VALUE));


    int right_top_x = BOARD_OFFSET_X + (BOARD_WIDTH * tile_size);
    int right_bottom_x = right_top_x;
    int right_top_y = BOARD_OFFSET_Y;
    int right_bottom_y = right_top_y + (BOARD_HEIGHT * tile_size);
    gfx_line(right_top_x, right_top_y, right_bottom_x, right_bottom_y, get_board_color(WALL_VALUE));
}

void draw_board(){
    for(int y = 0; y < BOARD_HEIGHT; y++){
        for(int x = 0; x < BOARD_WIDTH; x++){
        int board_value = board[y][x];

        if (board_value != EMPTY_SPACE_VALUE){
            draw_tile(x, y, get_board_color(board_value));
        }
        }
    }
}

void draw_active_piece(){
    for(int r = 0; r < 4; r++){
        for(int c = 0; c < 4; c++){
            int value = pieces[active_type][active_rotation][r][c];
            if(value != 0)
                draw_tile(active_x + c, active_y + r, get_board_color(value));
        }
    }
}

void draw_next_piece(){
    for(int r = 0; r < 4; r++){
        for(int c = 0; c < 4; c++){
            int value = pieces[next_type][0][r][c];
            if(value != 0)
            draw_tile(NEXT_BLOCK_X + c, NEXT_BLOCK_Y + r, get_board_color(value));
        }
    }
}

void draw_end_screen(){
    gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, RED);
    gfx_textout(gfx_screenWidth() / 2, gfx_screenHeight() / 2, "Game Over!", WHITE);
}
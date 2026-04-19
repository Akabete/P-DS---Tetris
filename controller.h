#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "settings.h"
#include "primlib.h"
#include "model.h"


void horizontal_movement_handler();
void rotation_handler();
void hard_drop_handler();

void input_handler();

int game_over_quit();
void running_game_quit(int pressed_key);

#endif
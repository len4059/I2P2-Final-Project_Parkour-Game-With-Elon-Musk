#include "Global.h"
#include "shapes/Shape.h"

Scenetype window = Scenetype::Menu;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES] = {false};
Point mouse;
bool debug_mode = true;
RectangleParams normal_block = {-1,false, true, true,false, 0.0, 0.0, 0.0, 0.0};
RectangleParams ice_block = {-1, false, true, false, false, 0.0, 0.0, 0.0, 0.0};
RectangleParams fire_block = {-1,false, true, true, true, 0.0, 0.0, 0.0, 0.0};
RectangleParams invisible_block = {-1,false, false, true,false, 0.0, 0.0, 0.0, 0.0};
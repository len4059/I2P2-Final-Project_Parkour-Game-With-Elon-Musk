#include "Introduction.h"
#include "../Utils.h"
#include "../data/DataCenter.h"
#include "../data/OperationCenter.h"
#include "../data/SoundCenter.h"
#include "../data/ImageCenter.h"
#include "../data/FontCenter.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <iostream>

Introduction::Introduction(){
    init();
}

Introduction::~Introduction(){
    destroy();
}

void Introduction::init(){
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();
    Platform *PLT=DC->platforms;

    SC->init();
	FC->init();

    background_img = IC->get(Resource::introduction_background_img_path);
    earth_wall = IC->get(Resource::earth_wall);

    mode[1]=normal_block;

    DC->platforms->loadmap(Resource::map_introduction,mode,DC->window_width, DC->window_height);

    DC->platforms->textures[1] = earth_wall;

    DC->platforms->init();
	DC->hero->init();
	hero_init();

    back_button_width = 200;
    back_button_height = 90;

    back_button_x = (DC->window_width - back_button_width) / 20 * 1;
    back_button_y = (DC->window_height - back_button_height) / 20 * 1;

    button_color = al_map_rgb(255, 180, 100);         
    button_hover_color = al_map_rgb(255, 230, 150);  

    back_button_current_color = button_color;
}

bool Introduction::update(){
    DataCenter* DC = DataCenter::get_instance();

    if (DC->mouse.x >= back_button_x && DC->mouse.x <= back_button_x + back_button_width &&
        DC->mouse.y >= back_button_y && DC->mouse.y <= back_button_y + back_button_height) {
            back_button_current_color = button_hover_color; 
            if (DC->mouse_state[1]) { 
                std::cout << "Button clicked! Switching to Menu." << std::endl;
                window = Scenetype::Menu;  
                return false;  
            }
        }
    else if(DC->key_state[ALLEGRO_KEY_ESCAPE]){
        std::cout << "Button clicked! Switching to Menu." << std::endl;
        window = Scenetype::Menu;  
        return false; 
    }
    else back_button_current_color = button_color;

    DC->hero->update();
    DC->platforms->update();

    memcpy(DC->prev_key_state, DC->key_state, sizeof(DC->key_state));
	memcpy(DC->prev_mouse_state, DC->mouse_state, sizeof(DC->mouse_state));

    return true;
}

void Introduction::draw(){
    DataCenter *DC = DataCenter::get_instance();
    FontCenter* FC = FontCenter::get_instance();

    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background_img, 0, 0, 0);

    al_draw_filled_rectangle(back_button_x, back_button_y, back_button_x + back_button_width, back_button_y + back_button_height, back_button_current_color);

    al_draw_rectangle(back_button_x, back_button_y, back_button_x + back_button_width, back_button_y + back_button_height, al_map_rgb(0, 0, 0), 2);

    al_draw_text(FC->caviar_dreams[24], al_map_rgb(0, 0, 0),
                 back_button_x + back_button_width / 2, back_button_y + back_button_height / 2 - 12,
                 ALLEGRO_ALIGN_CENTER, "BACK");

    DC->hero->draw();
	DC->platforms->draw();
}

void Introduction::destroy(){

}

void Introduction::hero_init(){
	DataCenter *DC = DataCenter::get_instance();
	Platform *PLT=DC->platforms;
	DC->hero->hero_died = false;
	DC->hero->dash_length = PLT->get_block_height();
	DC->hero->dash_duration = 0.1*DC->FPS;
	DC->hero->max_jump_height = PLT->get_block_height()*3;
	DC->hero->max_jump_speed = -std::sqrt(1.5*DC->hero->up_gravity * DC->hero->max_jump_height);
	DC->hero->climb_speed = DC->hero->max_jump_speed/1.82;
    DC->hero->hp = 0;

    double spawn_x = DC->window_width/20 * 2;
	double spawn_y = DC->window_height/12 * 11;

	Rectangle* rect = dynamic_cast<Rectangle*>(DC->hero->shape.get());
    if (rect) {
        rect->update_center_x(spawn_x);
        rect->update_center_y(spawn_y);
    }
}
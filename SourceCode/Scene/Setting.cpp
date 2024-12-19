#include "Setting.h"
#include "../Utils.h"
#include "../data/DataCenter.h"
#include "../data/OperationCenter.h"
#include "../data/SoundCenter.h"
#include "../data/ImageCenter.h"
#include "../data/FontCenter.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <iostream>

Setting::Setting(){
    init();
}

Setting::~Setting(){
    destroy();
}

void Setting::init(){
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    background_img = IC->get(Resource::setting_background_img_path);

    back_button_width = 200;
    back_button_height = 90;

    back_button_x = (DC->window_width - back_button_width) / 20 * 1;
    back_button_y = (DC->window_height - back_button_height) / 20 * 1;

    button_color = al_map_rgb(255, 180, 100);         
    button_hover_color = al_map_rgb(255, 230, 150);  

    back_button_current_color = button_color;

    SC->init();
	FC->init();
}

bool Setting::update(){
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

    return true;
}

void Setting::draw(){
    DataCenter *DC = DataCenter::get_instance();
    FontCenter* FC = FontCenter::get_instance();

    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background_img, 0, 0, 0);

    al_draw_filled_rectangle(back_button_x, back_button_y, back_button_x + back_button_width, back_button_y + back_button_height, back_button_current_color);

    al_draw_rectangle(back_button_x, back_button_y, back_button_x + back_button_width, back_button_y + back_button_height, al_map_rgb(0, 0, 0), 2);

    al_draw_text(FC->caviar_dreams[24], al_map_rgb(0, 0, 0),
                 back_button_x + back_button_width / 2, back_button_y + back_button_height / 2 - 12,
                 ALLEGRO_ALIGN_CENTER, "BACK");
}

void Setting::destroy(){

}
#include "earth2_to_moon.h"
#include "../Utils.h"
#include "../data/DataCenter.h"
#include "../data/OperationCenter.h"
#include "../data/SoundCenter.h"
#include "../data/ImageCenter.h"
#include "../data/FontCenter.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <iostream>

e2tomoon::e2tomoon(){
    init();
}

e2tomoon::~e2tomoon(){
    destroy();
}

void e2tomoon::init(){
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    SC->init();
	FC->init();

    timer = 0;
}

bool e2tomoon::update(){
    DataCenter* DC = DataCenter::get_instance();

    timer++;
    if(timer >= 90){
        window = Scenetype::Game_moon;
        return false;
    }
    return true;
}

void e2tomoon::draw(){
    DataCenter *DC = DataCenter::get_instance();
    FontCenter* FC = FontCenter::get_instance();

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_text(
        FC->caviar_dreams[FontSize::LARGE], 
        al_map_rgb(255, 255, 255), 
        DC->window_width / 2, 
        DC->window_height / 2 - al_get_font_line_height(FC->caviar_dreams[FontSize::LARGE]) / 2, 
        ALLEGRO_ALIGN_CENTRE, 
        "flying to the moon"
    );
}

void e2tomoon::destroy(){

}
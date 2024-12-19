/*
#include "moon1_to_moon2.h"
#include "../Utils.h"
#include "../data/DataCenter.h"
#include "../data/OperationCenter.h"
#include "../data/SoundCenter.h"
#include "../data/ImageCenter.h"
#include "../data/FontCenter.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <iostream>

m1tom2::m1tom2(){
    init();
}

m1tom2::~m1tom2(){
    destroy();
}

void m1tom2::init(){
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    SC->init();
	FC->init();

    timer = 0;
}

bool m1tom2::update(){
    DataCenter* DC = DataCenter::get_instance();

    timer++;
    if(timer >= 90){
        window = Scenetype::Game_moon_2;
        return false;
    }
    return true;
}

void m1tom2::draw(){
    DataCenter *DC = DataCenter::get_instance();
    FontCenter* FC = FontCenter::get_instance();

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_text(
        FC->caviar_dreams[FontSize::LARGE], 
        al_map_rgb(255, 255, 255), 
        DC->window_width / 2, 
        DC->window_height / 2 - al_get_font_line_height(FC->caviar_dreams[FontSize::LARGE]) / 2, 
        ALLEGRO_ALIGN_CENTRE, 
        "moving to moon-2"
    );
}

void m1tom2::destroy(){

}
*/
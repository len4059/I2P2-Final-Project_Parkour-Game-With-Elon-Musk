#include "moon_to_mars.h"
#include "../Utils.h"
#include "../data/DataCenter.h"
#include "../data/OperationCenter.h"
#include "../data/SoundCenter.h"
#include "../data/ImageCenter.h"
#include "../data/FontCenter.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <iostream>

moon2mars::moon2mars(){
    init();
}

moon2mars::~moon2mars(){
    destroy();
}

void moon2mars::init(){
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    SC->init();
	FC->init();

    timer = 0;
}

bool moon2mars::update(){
    DataCenter* DC = DataCenter::get_instance();

    timer++;
    if(timer >= 90){
        window = Scenetype::Game_mars;
        return false;
    }
    return true;
}

void moon2mars::draw(){
    DataCenter *DC = DataCenter::get_instance();
    FontCenter* FC = FontCenter::get_instance();

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_text(
        FC->caviar_dreams[FontSize::LARGE], 
        al_map_rgb(255, 255, 255), 
        DC->window_width / 2, 
        DC->window_height / 2 - al_get_font_line_height(FC->caviar_dreams[FontSize::LARGE]) / 2, 
        ALLEGRO_ALIGN_CENTRE, 
        "OMG! IT'S MARS!"
    );
}

void moon2mars::destroy(){

}
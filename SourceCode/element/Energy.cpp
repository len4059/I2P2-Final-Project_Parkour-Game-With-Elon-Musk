#include "Energy.h"
#include "../Resource.h"
#include <fstream>
#include <iostream>
#include <allegro5/allegro_primitives.h>
Energy::Energy(){
}
Energy::~Energy(){
}

void Energy::init(){
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    energy = IC->get(Resource::energy);

    img_width = al_get_bitmap_width(energy);
    img_height = al_get_bitmap_height(energy);

    RectangleParams energy_box=normal_block;
    shape.reset(
        new Rectangle(
            DC->window_width/20*5,
            DC->window_height/12*10,
            DC->window_width/20*5 + img_width,
            DC->window_height/12*10 + img_height,
            0,
            energy_box
        )
    );
    collected=false;
    timer=restore_time;
}

void Energy::update(){
    if(collected){
        timer--;
        if(timer<=0){
            collected=false;
            timer=restore_time;
        }
    }
    else{
        DataCenter *DC = DataCenter::get_instance();
        SoundCenter *SC = SoundCenter::get_instance();
        ImageCenter *IC = ImageCenter::get_instance();
        FontCenter *FC = FontCenter::get_instance();
        Hero *hero = DC->hero;

        if (!hero || !hero->shape) {
            std::cerr << "Hero or Hero shape is not initialized." << std::endl;
            return;
        }
        if(shape->overlap(*hero->shape)){
           collected=true;
           hero->up_dash()=true;
        }
    }
}

void Energy::draw(){
    if(collected) return;

    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    Rectangle *rect = dynamic_cast<Rectangle*>(shape.get());
    al_draw_bitmap(
        energy,
        rect->center_x() - img_width / 2.0,
        rect->center_y() - img_height / 2.0,
        0
    );
}
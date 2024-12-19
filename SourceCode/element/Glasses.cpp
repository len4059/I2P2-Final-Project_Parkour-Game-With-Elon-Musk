#include "Glasses.h"
#include "../Resource.h"
#include <fstream>
#include <iostream>
#include <allegro5/allegro_primitives.h>

void Glasses::init(){
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    glasses = IC->get(Resource::tool_glass);

    img_width = al_get_bitmap_width(glasses);
    img_height = al_get_bitmap_height(glasses);

    RectangleParams glasses =normal_block;


    shape.reset(
        new Rectangle(
            DC->window_width/20*6,
            DC->window_height/12,
            DC->window_width/20*6 + img_width,
            DC->window_height/12 + img_height,
            0,
            glasses
        )
    );

    glasses_collected = false;
}

void Glasses::update(){
    if(glasses_collected) return;

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
        glasses_collected = true;
    }
}

void Glasses::draw(){
    if(glasses_collected) return;

    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    Rectangle *rect = dynamic_cast<Rectangle*>(shape.get());
    al_draw_bitmap(
        glasses,
        rect->center_x() - img_width / 2.0,
        rect->center_y() - img_height / 2.0,
        0
    );
}
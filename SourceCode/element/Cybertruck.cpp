#include "Cybertruck.h"
#include "../Resource.h"
#include <fstream>
#include <iostream>
#include <allegro5/allegro_primitives.h>

void Cybertruck::init(){
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    Cybertruck = IC->get(Resource::cybertruck);

    img_width = al_get_bitmap_width(Cybertruck);
    img_height = al_get_bitmap_height(Cybertruck);

    RectangleParams Cybertruck = normal_block;


    shape.reset(
        new Rectangle(
            DC->window_width/20 * 1,
            DC->window_height/12 * 5.5,
            DC->window_width/20 * 1 + img_width,
            DC->window_height/12 * 5.5 + img_height,
            0,
            Cybertruck
        )
    );

    isgoing_up = false;
    move_up_frames_left = 0;
    move_up_speed = 6;
}

void Cybertruck::update(){
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    Hero *hero = DC->hero;

    if(shape->overlap(*hero->shape)){
        if(DC->key_state[ALLEGRO_KEY_T]){
            isgoing_up = true;
            move_up_frames_left = 200;
        }
    }

    if(isgoing_up && move_up_frames_left > 0){
        Cybertruck_rect = dynamic_cast<Rectangle*>(shape.get());
        hero_rect = dynamic_cast<Rectangle*>(hero->shape.get());

        Cybertruck_rect->x1 -= move_up_speed;
        Cybertruck_rect->x2 -= move_up_speed;

        hero_rect->update_center_x(hero_rect->center_x() - move_up_speed);

        move_up_frames_left--;

        if(move_up_frames_left <= 0) isgoing_up = false;
    }
}

void Cybertruck::draw(){

    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    Rectangle *rect = dynamic_cast<Rectangle*>(shape.get());
    al_draw_bitmap(
        Cybertruck,
        rect->center_x() - img_width / 2.0,
        rect->center_y() - img_height / 2.0,
        0
    );
}
#include "Moon_to_mars_rocket.h"
#include "../Resource.h"
#include <fstream>
#include <iostream>
#include <allegro5/allegro_primitives.h>

void Rocket2::init(){
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    Rocket2 = IC->get(Resource::moon_to_mars_rocket);

    img_width = al_get_bitmap_width(Rocket2);
    img_height = al_get_bitmap_height(Rocket2);

    RectangleParams Rocket2 = normal_block;


    shape.reset(
        new Rectangle(
            DC->window_width/20 * 4.5,
            DC->window_height/12 - 70,
            DC->window_width/20 * 4.5 + img_width,
            DC->window_height/12 - 70 + img_height,
            0,
            Rocket2
        )
    );

    isgoing_up = false;
    move_up_frames_left = 0;
    move_up_speed = 6;
}

void Rocket2::update(){
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    Hero *hero = DC->hero;

    if(shape->overlap(*hero->shape)){
        if(DC->key_state[ALLEGRO_KEY_T]){
            isgoing_up = true;
            move_up_frames_left = 50;
        }
    }

    if(isgoing_up && move_up_frames_left > 0){
        rocket2_rect = dynamic_cast<Rectangle*>(shape.get());
        hero_rect = dynamic_cast<Rectangle*>(hero->shape.get());

        rocket2_rect->y1 -= move_up_speed;
        rocket2_rect->y2 -= move_up_speed;

        hero_rect->update_center_y(hero_rect->center_y() - move_up_speed);

        move_up_frames_left--;

        if(move_up_frames_left <= 0) isgoing_up = false;
    }
}

void Rocket2::draw(){

    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    Rectangle *rect = dynamic_cast<Rectangle*>(shape.get());
    al_draw_bitmap(
        Rocket2,
        rect->center_x() - img_width / 2.0,
        rect->center_y() - img_height / 2.0,
        0
    );
}
#include "Earth_to_moon_rocket.h"
#include "../Resource.h"
#include <fstream>
#include <iostream>
#include <allegro5/allegro_primitives.h>

void Rocket::init(){
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    Rocket = IC->get(Resource::earth_to_moon_rocket);

    img_width = al_get_bitmap_width(Rocket);
    img_height = al_get_bitmap_height(Rocket);

    RectangleParams Rocket = normal_block;


    shape.reset(
        new Rectangle(
            DC->window_width/20 * 16,
            DC->window_height/12 * 8.5,
            DC->window_width/20 * 16 + img_width,
            DC->window_height/12 * 8.5 + img_height,
            0,
            Rocket
        )
    );

    isgoing_up = false;
    move_up_frames_left = 0;
    move_up_speed = 6;
}

void Rocket::update(){
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
        rocket_rect = dynamic_cast<Rectangle*>(shape.get());
        hero_rect = dynamic_cast<Rectangle*>(hero->shape.get());

        rocket_rect->y1 -= move_up_speed;
        rocket_rect->y2 -= move_up_speed;

        hero_rect->update_center_y(hero_rect->center_y() - move_up_speed);

        move_up_frames_left--;

        if(move_up_frames_left <= 0) isgoing_up = false;
    }
}

void Rocket::draw(){

    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    Rectangle *rect = dynamic_cast<Rectangle*>(shape.get());
    al_draw_bitmap(
        Rocket,
        rect->center_x() - img_width / 2.0,
        rect->center_y() - img_height / 2.0,
        0
    );
}
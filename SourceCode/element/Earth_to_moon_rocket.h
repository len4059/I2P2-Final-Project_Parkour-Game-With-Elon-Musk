#ifndef ROCKET_H
#define ROCKET_H

#include "Object.h"
#include "../shapes/Rectangle.h"
#include <string>
#include <vector>
#include <map>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>

#include "../data/DataCenter.h"
#include "../data/OperationCenter.h"
#include "../data/SoundCenter.h"
#include "../data/ImageCenter.h"
#include "../data/FontCenter.h"

#include "../Scene/Gamescene_earth_2.h"

#include "Hero.h"

class Rocket : public Object{
    public:
        void init();
        void update();
        void draw() override;
        friend class Gamescene_earth2;
        friend class Hero;
    private:
        ALLEGRO_BITMAP *Rocket;

        Rectangle* rocket_rect;
        Rectangle* hero_rect;
        
        int img_width;
        int img_height;

        bool isgoing_up;
        int move_up_frames_left;    
        int move_up_speed; 
};

#endif
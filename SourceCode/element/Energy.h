#ifndef Energy_H
#define Energy_H

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

#include "../Scene/Gamescene_mars.h"

#include "Hero.h"
#include "Platform.h"
class Energy : public Object{
    public:
        Energy();
        ~Energy();
        void init();
        void update();
        void draw() override;
        friend class Platform;
        friend class Gamescene_mars;
    private:
        ALLEGRO_BITMAP *energy;
        int img_width;
        int img_height;
        int timer;
        bool collected;
        int restore_time=100;
};

#endif
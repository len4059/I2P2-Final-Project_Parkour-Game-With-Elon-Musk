#ifndef GLASSES_H
#define GLASSES_H

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
#include "Platform.h"
class Glasses : public Object{
    public:
        void init();
        void update();
        void draw() override;
        friend class Platform;
        friend class Gamescene_earth2;
    private:
        ALLEGRO_BITMAP *glasses;
        int img_width;
        int img_height;
        bool glasses_collected = false;
};

#endif
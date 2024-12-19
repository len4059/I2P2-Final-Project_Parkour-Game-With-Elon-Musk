#ifndef INTRODUCTION_H_INCLUDED
#define INTRODUCTION_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include "../UI.h"
#include "scene.h"
#include "../Global.h"
#include "Scenemanager.h"

#include "../element/Hero.h"
#include "../element/Platform.h"

class Introduction : public Scene{
    public:
        Introduction();
        ~Introduction();
        void init() override;
        bool update() override;
        void draw() override;
        void destroy() override;

        void hero_init();
    private:
        double back_button_x, back_button_y, back_button_width, back_button_height;
        ALLEGRO_COLOR button_color;
        ALLEGRO_COLOR button_hover_color;
        ALLEGRO_COLOR back_button_current_color;

        ALLEGRO_BITMAP *background_img;
        ALLEGRO_SAMPLE_INSTANCE *background_music;

        bool BGM_played;

        ALLEGRO_BITMAP *earth_wall;
        std::map<int,RectangleParams>mode;
};

#endif
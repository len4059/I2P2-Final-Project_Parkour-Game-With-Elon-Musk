#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

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

class Menu : public Scene{
    public:
        Menu();
        ~Menu();
        void init() override;
	    bool update() override;
	    void draw() override;
        void destroy() override;
    private:
        double play_button_x, play_button_y, play_button_width, play_button_height;
        double setting_button_x, setting_button_y, setting_button_width, setting_button_height;
        double introduction_button_x, introduction_button_y, introduction_button_width, introduction_button_height;
        double exit_button_x, exit_button_y, exit_button_width, exit_button_height;

        ALLEGRO_COLOR button_color;
        ALLEGRO_COLOR button_hover_color;
        ALLEGRO_COLOR play_button_current_color, setting_button_current_color, introduction_button_current_color, exit_button_current_color;

        ALLEGRO_BITMAP *background_img;
        ALLEGRO_SAMPLE_INSTANCE *background_music;

        bool BGM_played;
};      

#endif
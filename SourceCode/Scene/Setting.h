#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED

#include <allegro5/allegro.h>
#include "../UI.h"
#include "scene.h"
#include "../Global.h"
#include "Scenemanager.h"

class Setting : public Scene{
    public:
        Setting();
        ~Setting();
        void init() override;
        bool update() override;
        void draw() override;
        void destroy() override;
    private:
        double back_button_x, back_button_y, back_button_width, back_button_height;
        ALLEGRO_COLOR button_color;
        ALLEGRO_COLOR button_hover_color;
        ALLEGRO_COLOR back_button_current_color;

        ALLEGRO_BITMAP *background_img;
};

#endif
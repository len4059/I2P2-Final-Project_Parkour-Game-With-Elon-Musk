#ifndef ENDING_H_INCLUDED
#define ENDING_H_INCLUDED

#include <allegro5/allegro.h>
#include "../data/GIFCenter.h"
#include "../UI.h"
#include "scene.h"
#include "../Global.h"
#include "Scenemanager.h"

class Ending : public Scene{
    public:
        Ending();
        ~Ending();
        void init() override;
        bool update() override;
        void draw() override;
        void destroy() override;
    private:
        double menu_button_x, menu_button_y, tryagain_button_x, tryagain_button_y, button_width, button_height;
        ALLEGRO_COLOR button_color;
        ALLEGRO_COLOR button_hover_color;
        ALLEGRO_COLOR menu_button_current_color;

        ALLEGRO_COLOR tryagain_button_current_color;

        ALLEGRO_BITMAP *background_img;

        ALGIF_ANIMATION *gif;
};

#endif
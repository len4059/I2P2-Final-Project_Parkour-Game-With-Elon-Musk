#ifndef MOON_TO_MARS_INCLUDED
#define MOON_TO_MARS_INCLUDED

#include <allegro5/allegro.h>
#include "../UI.h"
#include "scene.h"
#include "../Global.h"
#include "Scenemanager.h"

class moon2mars : public Scene{
    public:
        moon2mars();
        ~moon2mars();
        void init() override;
        bool update() override;
        void draw() override;
        void destroy() override;
    private:
        double timer;
};

#endif
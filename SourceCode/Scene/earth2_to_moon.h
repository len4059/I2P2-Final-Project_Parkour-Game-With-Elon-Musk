#ifndef EARTH2_TO_MOON_INCLUDED
#define EARTH2_TO_MOON_INCLUDED

#include <allegro5/allegro.h>
#include "../UI.h"
#include "scene.h"
#include "../Global.h"
#include "Scenemanager.h"

class e2tomoon : public Scene{
    public:
        e2tomoon();
        ~e2tomoon();
        void init() override;
        bool update() override;
        void draw() override;
        void destroy() override;
    private:
        double timer;
};

#endif
#ifndef EARTH1_TO_EARTH2_INCLUDED
#define EARTH1_TO_EARTH2_INCLUDED

#include <allegro5/allegro.h>
#include "../UI.h"
#include "scene.h"
#include "../Global.h"
#include "Scenemanager.h"

class e1toe2 : public Scene{
    public:
        e1toe2();
        ~e1toe2();
        void init() override;
        bool update() override;
        void draw() override;
        void destroy() override;
    private:
        double timer;
};

#endif
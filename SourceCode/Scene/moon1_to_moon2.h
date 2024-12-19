/*
#ifndef MOON1_TO_MOON2_INCLUDED
#define MOON1_TO_MOON2_INCLUDED

#include <allegro5/allegro.h>
#include "../UI.h"
#include "scene.h"
#include "../Global.h"
#include "Scenemanager.h"

class m1tom2 : public Scene{
    public:
        m1tom2();
        ~m1tom2();
        void init() override;
        bool update() override;
        void draw() override;
        void destroy() override;
    private:
        double timer;
};

#endif
*/
#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED

#include "Scene.h"
#include <memory>
#include "../Global.h"

class Scenemanager{
    public:
        Scenemanager();
        ~Scenemanager();

        void Create_Scene(Scenetype&);
        bool update_Scene();
        void draw_Scene();
    private:
        Scene *currentScene;
};

#endif
#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

class Scene {
public:
    Scene() {}
    virtual ~Scene() {}

    virtual void init() = 0;
    virtual bool update() = 0;
    virtual void draw() = 0;
    virtual void destroy() = 0;
};

#endif

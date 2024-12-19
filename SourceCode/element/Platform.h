#ifndef PLATFORM_H
#define PLATFORM_H

#include "Object.h"
#include "../shapes/Rectangle.h"
#include <string>
#include <vector>
#include <map>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>

#include "../data/DataCenter.h"
#include "../data/OperationCenter.h"
#include "../data/SoundCenter.h"
#include "../data/ImageCenter.h"
#include "../data/FontCenter.h"

class Platform : public Object{
    public:
        Platform();
        void loadmap(const std::string& map,std::map<int,RectangleParams>mode, int window_width, int window_height);
        void init() ;
        void update() ;
        void draw() override;
        double get_block_width(){
            return block_width;
        }
        double get_block_height(){
            return block_height;
        }
        const std::vector<Rectangle>& get_platforms() const;

        std::map<int, ALLEGRO_BITMAP*> textures;
    private:
        std::vector<Rectangle> rectangles;
        double block_height;
        double block_width;
        double x_buffer=5;
        double y_buffer=5;
        bool debug=false;
};

#endif
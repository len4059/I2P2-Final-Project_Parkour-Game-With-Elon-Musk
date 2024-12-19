#include "Platform.h"
#include "../Resource.h"
#include <fstream>
#include <iostream>
#include <allegro5/allegro_primitives.h>
#include"Hero.h"
#include"Glasses.h"
Platform::Platform(){

}
void Platform::loadmap(const std::string& map, std::map<int,RectangleParams>mode, int window_width, int window_height){
    rectangles.clear();
    textures.clear();
    block_width = window_width / 20.0;
    block_height = window_height / 12.0;    
    DataCenter *DC = DataCenter::get_instance();
    std::ifstream file(map);

    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << map << std::endl;
        return;
    }

    std::string line;

    int row = 0;
    while(std::getline(file, line)){
        for (size_t col = 0; col < line.size(); ++col) {
            if (line[col] >= '1' && line[col] <= '9') { 
                int type = line[col] - '0';
                double x1 = col * block_width;
                double y1 = row * block_height;
                double x2 = x1 + block_width;
                double y2 = y1 + block_height;
                if(mode.find(type)!=mode.end())
                    rectangles.emplace_back(x1,y1,x2,y2,type,mode[type]);
                }
            }
            ++row; 
        }
       
    file.close();
}

void Platform::init(){

}
void moveRectangle(Hero *hero, const Rectangle &velocity) {
    hero->get_x_speed() += velocity.vx;
    hero->get_y_speed() += velocity.vy;
}
void Platform::update() {
    DataCenter *DC = DataCenter::get_instance();
    Hero *hero=DC->hero;
    Rectangle h_rect=*dynamic_cast<Rectangle*>(hero->shape.get());
    Rectangle &modify_h_rect=*dynamic_cast<Rectangle*>(hero->shape.get());
    for (auto& rect : rectangles) {
        if (rect.can_move) {
            bool Left=(h_rect.x2+rect.detect_range)>rect.x1 && h_rect.x1 <rect.x1;
            bool Right=h_rect.x1<(rect.x2+rect.detect_range) && h_rect.x2>rect.x1;
            bool Up=(h_rect.y2+rect.detect_range)>rect.y1 && h_rect.y1 < rect.y1;
            bool Down=(h_rect.y1<(rect.y2+rect.detect_range) && h_rect.y2>rect.y1);
            switch(rect.move_type){
                case 1:
                    rect.x1 += rect.vx;
                    rect.x2 += rect.vx;    
                    if (rect.x1 <rect.boundary_1 || rect.x2 >rect.boundary_2)                
                        rect.vx = -rect.vx;
                    break; 
                case 2:
                    rect.y1 += rect.vy;
                    rect.y2 += rect.vy;
                    if (rect.y1 <rect.boundary_1 || rect.y2 >rect.boundary_2) 
                        rect.vy = -rect.vy; 
                    break;
                case 3:{
                    switch(rect.detect_side){
                        case Detect_side::L:
                            if(Left)
                                rect.move_type=5;
                            break;
                        case Detect_side::R:
                            if(Right)
                                rect.move_type=5;
                            break;
                        case Detect_side::U:
                            if(Up)
                                rect.move_type=5;
                            break;
                        case Detect_side::D:
                            if(Down)
                                rect.move_type=5;
                            break;
                        case Detect_side::LAR:
                            if(Left && Right)
                                rect.move_type=5;
                            break;
                        case Detect_side::LAU:
                            if(Left && Up)
                                rect.move_type=5;
                            break;
                        case Detect_side::LAD:
                            if(Left && Down)
                                rect.move_type=5;
                            break;
                        case Detect_side::RAU:
                            if(Right && Up)
                                rect.move_type=5;
                            break;
                        case Detect_side::RAD:
                            if(Right && Down)
                                rect.move_type=5;
                            break;
                        case Detect_side::LOR:
                            if(Left || Right)
                                rect.move_type=5;
                            break;
                        case Detect_side::LOU:
                            if(Left || Up)
                                rect.move_type=5;
                            break;
                        case Detect_side::LOD:
                            if(Left || Down)
                                rect.move_type=5;
                            break;
                        case Detect_side::ROU:
                            if(Right || Up)
                                rect.move_type=5;
                            break;
                        case Detect_side::ROD:
                            if(Right || Down)
                                rect.move_type=5;
                            break;
                        case Detect_side::UOD:
                            if(Up || Down)
                                rect.move_type=5;
                            break;
                        case Detect_side::LORAD:
                            if(h_rect.y1>rect.y2 &&(Left||Right))
                                rect.move_type=5;
                            break;
                    }
                    break;
                }
                case 4:{
                     switch(rect.detect_side){
                        case Detect_side::L:
                            if(Left)
                                rect.move_type=6;
                            break;
                        case Detect_side::R:
                            if(Right)
                                rect.move_type=6;
                            break;
                        case Detect_side::U:
                            if(Up)
                                rect.move_type=6;
                            break;
                        case Detect_side::D:
                            if(Down)
                                rect.move_type=6;
                            break;
                        case Detect_side::LAR:
                            if(Left && Right)
                                rect.move_type=6;
                            break;
                        case Detect_side::LAU:
                            if(Left && Up)
                                rect.move_type=6;
                            break;
                        case Detect_side::LAD:
                            if(Left && Down)
                                rect.move_type=6;
                            break;
                        case Detect_side::RAU:
                            if(Right && Up)
                                rect.move_type=6;
                            break;
                        case Detect_side::RAD:
                            if(Right && Down)
                                rect.move_type=6;
                            break;
                        case Detect_side::LOR:
                            if(Left || Right)
                                rect.move_type=5;
                            break;
                        case Detect_side::LOU:
                            if(Left || Up)
                                rect.move_type=6;
                            break;
                        case Detect_side::LOD:
                            if(Left || Down)
                                rect.move_type=6;
                            break;
                        case Detect_side::ROU:
                            if(Right || Up)
                                rect.move_type=6;
                            break;
                        case Detect_side::ROD:
                            if(Right || Down)
                                rect.move_type=6;
                            break;
                        case Detect_side::UOD:
                            if(Up || Down)
                                rect.move_type=6;
                            break;
                        case Detect_side::UODAR:
                            if(h_rect.x1>rect.x2 &&(Up || Down))
                                rect.move_type=6;
                            break;
                    }
                    break;
                }
                case 5:
                    rect.y1 += rect.vy;
                    rect.y2 += rect.vy;
                    if(!rect.dir && ((rect.vy>0 && rect.y2>rect.boundary_2) || (rect.vy<0 && rect.y1<rect.boundary_2))){
                        rect.vy = -rect.vy; 
                        rect.dir=true;
                    }
                    else if(rect.dir){
                        if(rect.vy<0 && rect.y1<rect.boundary_1){
                            rect.update_center_y(rect.boundary_1+block_height/2);
                            rect.vy = -rect.vy; 
                            rect.dir=false;
                            rect.move_type=3;
                        }
                        else if(rect.vy>0 && rect.y2>rect.boundary_1){
                            rect.update_center_y(rect.boundary_1-block_height/2);
                            rect.vy = -rect.vy; 
                            rect.dir=false;
                            rect.move_type=3;
                        }
                    }
                    break;
                case 6:
                    rect.x1 += rect.vx;
                    rect.x2 += rect.vx;
                    if(!rect.dir && ((rect.vx>0 && rect.x2>rect.boundary_2) || (rect.vx<0 && rect.x1<rect.boundary_2))){
                        rect.vx = -rect.vx; 
                        rect.dir=true;
                    }
                    else if(rect.dir){
                        if(rect.vx<0 && rect.x1<rect.boundary_1){
                            rect.update_center_x(rect.boundary_1+block_width/2);
                            rect.vx=-rect.vx;
                            rect.dir=false;
                            rect.move_type=4;
                        }
                        else if(rect.vx>0 && rect.x2>rect.boundary_1){
                            rect.update_center_x(rect.boundary_1-block_width/2);
                            rect.vx=-rect.vx;
                            rect.dir=false;
                            rect.move_type=4;
                        }
                    }
                    break;
                case 8:
                    switch(rect.detect_side){
                        case Detect_side::L:
                            if(Left)
                               moveRectangle(hero, rect);
                            break;
                        case Detect_side::R:
                            if(Right)
                               moveRectangle(hero, rect);
                            break;
                        case Detect_side::U:
                            if(Up)
                                moveRectangle(hero, rect);
                            break;
                        case Detect_side::D:
                            if(Down)
                                 moveRectangle(hero, rect);
                            break;
                        case Detect_side::LAR:
                            if(Left && Right)
                                 moveRectangle(hero, rect);
                            break;
                        case Detect_side::LAU:
                            if(Left && Up)
                                 moveRectangle(hero, rect);
                            break;
                        case Detect_side::LAD:
                            if(Left && Down)
                                moveRectangle(hero, rect);
                            break;
                        case Detect_side::RAU:
                            if(Right && Up)
                                 moveRectangle(hero, rect);
                            break;
                        case Detect_side::RAD:
                            if(Right && Down)
                                moveRectangle(hero, rect);
                            break;
                        case Detect_side::LOR:
                            if(Left || Right)
                               moveRectangle(hero, rect);
                            break;
                        case Detect_side::LOU:
                            if(Left || Up)
                                moveRectangle(hero, rect);
                            break;
                        case Detect_side::LOD:
                            if(Left || Down)
                               moveRectangle(hero, rect);
                            break;
                        case Detect_side::ROU:
                            if(Right || Up)
                                moveRectangle(hero, rect);
                            break;
                        case Detect_side::ROD:
                            if(Right || Down)
                                 moveRectangle(hero, rect);
                            break;
                        case Detect_side::UOD:
                            if(Up || Down)
                               moveRectangle(hero, rect);
                            break;
                        case Detect_side::UODAR:
                            if(h_rect.x1>rect.x2 &&(Up || Down))
                                moveRectangle(hero, rect);
                            break;
                        case Detect_side::LORAU:
                            if((Left || Right)&&Up)
                                moveRectangle(hero, rect);
                            break;
                        case Detect_side::GU:
                            std::cout<<"in\n";
                            if(Up &&(((h_rect.x2+block_width/5)>rect.x1 && h_rect.x1 <=rect.x1) ||
                                h_rect.x1<(rect.x2+block_width/5) && h_rect.x2>=rect.x1)){
                                 moveRectangle(hero, rect);
                                 std::cout<<"out\n";
                            }
                            break;
                        case Detect_side::GD:
                            if(Down && (((h_rect.x2 + block_width / 5) > rect.x1 && h_rect.x1 <= rect.x1) || 
                                ((h_rect.x1 < (rect.x2 + block_width / 5)) && (h_rect.x2 >= rect.x1)))){
                                 moveRectangle(hero, rect);
                                 std::cout<<"test2:"<<h_rect.y2<<" "<<rect.y1<<std::endl;
                            }
                            break;
                        case Detect_side::GL:
                            if(Left &&(((h_rect.y2+block_height/5)>rect.y1 && h_rect.y1 <=rect.y1) ||
                                h_rect.y1<(rect.y2+block_height/5) && h_rect.y2>=rect.y1)){
                                 moveRectangle(hero, rect);
                                 std::cout<<"test1:"<<h_rect.x2<<" "<<rect.x2<<std::endl;
                            }
                            break;
                        case Detect_side::GR:
                            if(Right &&(((h_rect.y2+block_height/5)>rect.y1 && h_rect.y1 <=rect.y1) ||
                                h_rect.y1<(rect.y2+block_height/5) && h_rect.y2>=rect.y1)){
                                 moveRectangle(hero, rect);
                                 std::cout<<"test1:"<<h_rect.x2<<" "<<rect.x2<<std::endl;
                            }
                            break;
                        
                    }
                    break;
            }
        }
    }
}


void Platform::draw() {
    DataCenter *DC = DataCenter::get_instance();
    Glasses *glasses=DC->glasses;
    for (const auto& rect : rectangles) {
        ALLEGRO_BITMAP* texture = textures[rect.texture_type];
        if((glasses->glasses_collected ||rect.visible) && texture){
            al_draw_scaled_bitmap(
                texture,
                0, 0, al_get_bitmap_width(texture), al_get_bitmap_height(texture), 
                rect.x1, rect.y1, block_width, block_height, 
                0
            );
        }
        if(debug){
            al_draw_filled_rectangle(
                rect.x1, rect.y1, rect.x2, rect.y2,
                al_map_rgb(100, 100, 255)
            );
        }
    }
}

const std::vector<Rectangle>& Platform::get_platforms() const {
    return rectangles;
}
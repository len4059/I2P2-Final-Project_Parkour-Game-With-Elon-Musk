#include "Hero.h"
#include "../data/DataCenter.h"
#include "../data/GIFCenter.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <cstring>
namespace HeroSetting {
	static constexpr char gif_root_path[50] = "./assets/gif/Hero/hero";
	static constexpr char gif_state[][10] = {
		"run","stop","jump","hold"
	};
    static constexpr char gif_dir[][8]={
        "left","right","up","down"
    };
}
void Hero::init(){
    if(!gif_path_load){
        char buffer[60];
        for(size_t s_type=0;s_type < static_cast<size_t>(HeroState::MAX_STATE);s_type++){
            for(size_t d_type=0;d_type<static_cast<size_t>(HeroDir::MAX_DIR);d_type++){
                    sprintf(buffer,"%s_%s_%s.gif",
                            HeroSetting::gif_root_path,
                            HeroSetting::gif_state[static_cast<int>(s_type)],
                            HeroSetting::gif_dir[static_cast<int>(d_type)]
                    );
                    gifpath[{static_cast<HeroState>(s_type),static_cast<HeroDir>(d_type)}]=std::string{buffer};
                    sprintf(buffer,"%s_dash_%s_%s.gif",
                            HeroSetting::gif_root_path,
                            HeroSetting::gif_state[static_cast<int>(s_type)],
                            HeroSetting::gif_dir[static_cast<int>(d_type)]
                    );
                    gif_dashpath[{static_cast<HeroState>(s_type),static_cast<HeroDir>(d_type)}]=std::string{buffer};
                if(std::strcmp(HeroSetting::gif_state[static_cast<int>(s_type)], "jump") == 0){
                    sprintf(buffer,"%s_%s_%s_up.gif",
                            HeroSetting::gif_root_path,
                            HeroSetting::gif_state[static_cast<int>(s_type)],
                            HeroSetting::gif_dir[static_cast<int>(d_type)]
                    );
                    gifjump[{static_cast<HeroDir>(d_type),"up"}]=std::string{buffer};
                    sprintf(buffer,"%s_%s_%s_down.gif",
                            HeroSetting::gif_root_path,
                            HeroSetting::gif_state[static_cast<int>(s_type)],
                            HeroSetting::gif_dir[static_cast<int>(d_type)]
                        );
                    gifjump[{static_cast<HeroDir>(d_type),"down"}]=std::string{buffer};
                    sprintf(buffer,"%s_dash_%s_%s_down.gif",
                            HeroSetting::gif_root_path,
                            HeroSetting::gif_state[static_cast<int>(s_type)],
                            HeroSetting::gif_dir[static_cast<int>(d_type)]
                        );
                    gif_dashjump[{static_cast<HeroDir>(d_type),"down"}]=std::string{buffer};
                    sprintf(buffer,"%s_dash_%s_%s_up.gif",
                            HeroSetting::gif_root_path,
                            HeroSetting::gif_state[static_cast<int>(s_type)],
                            HeroSetting::gif_dir[static_cast<int>(d_type)]
                        );
                    gif_dashjump[{static_cast<HeroDir>(d_type),"up"}]=std::string{buffer};
                }
            }
        }  
        sprintf(buffer,"%s_%s_%s.gif",
                HeroSetting::gif_root_path,
                "stop",
                "up"
                );
        gifpath[{HeroState::STOP,HeroDir::UP}]=std::string{buffer};
        sprintf(buffer,"%s_dash_%s_%s.gif",
                HeroSetting::gif_root_path,
                "stop",
                "up"
                );
        gif_dashpath[{HeroState::STOP,HeroDir::UP}]=std::string{buffer};
        sprintf(buffer,"%s_%s_%s.gif",
                HeroSetting::gif_root_path,
                "stop",
                "down"
                );
        gifpath[{HeroState::STOP,HeroDir::DOWN}]=std::string{buffer};
        sprintf(buffer,"%s_dash_%s_%s.gif",
                HeroSetting::gif_root_path,
                "stop",
                "down"
                );
        gif_dashpath[{HeroState::STOP,HeroDir::DOWN}]=std::string{buffer};
        gif_path_load=true;
    }
    dir=HeroDir::RIGHT;
    state=HeroState::STOP;
    x_speed=0;
    y_speed=0;
    GIFCenter *GIFC = GIFCenter::get_instance();
    gif = GIFC->get(gifpath[{state,dir}]);
    DataCenter *DC = DataCenter::get_instance();
    Platform *PLT=DC->platforms;
    jump_redy=true;
    dash_redy=true;
    dash_control=false;
    hold=false;
    jump_add_timer=0;
    jump_timer=0;
    max_jump_height=PLT->get_block_height()*4;//static_cast<double>(gif->height*3);
    max_jump_speed=-std::sqrt(2 * up_gravity * max_jump_height);
    jump_cooldown=0; //static_cast<int>(DC->FPS/(max_jump_limit+1));
    double max_bvx=2*OnTheGround::MAX_SPEED;
    double max_bvy=-2*max_jump_speed;
    dash_length=PLT->get_block_height()*4;
    dash_duration=0.15*DataSetting::FPS;
    dash_speed=dash_length/dash_duration;
    dash_timer=0;
    double x_offset =0;
    double y_offset =0;
    RectangleParams hero=normal_block;
    shape.reset(
        new Rectangle(
            DC->window_width / 20 - DC->hero->gif->width / 2 + x_offset,
            (DC->window_height / 10) * 9 - DC->hero->gif->height / 2 + y_offset,
            DC->window_width / 20 + DC->hero->gif->width / 2 + x_offset,
            (DC->window_height / 10) * 9 + DC->hero->gif->height / 2 + y_offset,
            0,
            hero
        )
    );
    hero_died = false;
    hero_injured = false;
    hp = 3;
}
CollisionType Hero::detectCollision(const Rectangle& platform,double collision_buffer) {
    Rectangle rect = *dynamic_cast<Rectangle*>(shape.get());
    // Top collision (Hero's feet touching platform top)
    if (rect.y2 + collision_buffer >= platform.y1 && rect.y1 < platform.y1 &&
        rect.x2 > platform.x1+5&& rect.x1 < platform.x2-5&& y_speed >= 0) {
        return CollisionType::Top;
    }

    // Bottom collision (Hero's head hitting platform bottom)
    if (rect.y1< platform.y2 && rect.y2 > platform.y2 &&
        rect.x2-collision_buffer> platform.x1 && rect.x1+collision_buffer< platform.x2 && y_speed <= 0) {
        return CollisionType::Bottom;
    }

    // Left collision (Hero's right side hitting platform left side)
    if (rect.x2 >= platform.x1 && rect.x1 < platform.x1 &&
        rect.y2 > platform.y1 && rect.y1 < platform.y2 && x_speed >= 0) {
        return CollisionType::Left;
    }

    // Right collision (Hero's left side hitting platform right side)
    if (rect.x1 <= platform.x2 && rect.x2 > platform.x2 &&
        rect.y2 > platform.y1 && rect.y1 < platform.y2 && x_speed <= 0) {
        return CollisionType::Right;
    }

    return CollisionType::None;
}

double limitValue(double input, double maxAbsValue) {
    if (std::abs(input) > maxAbsValue) { 
        return (input > 0) ? maxAbsValue : -maxAbsValue;
    }
    return input;
}

void Hero::update(){
    DataCenter* DC = DataCenter::get_instance();
    Platform* platforms = DC->platforms;
    Rocket *rocket = DC->rocket;
    Rocket2 *rocket2 = DC->rocket2;
    Cybertruck *cybertruck = DC->cybertruck;
    Rectangle* rocket_rect = dynamic_cast<Rectangle*>(rocket->shape.get());
    Rectangle* rocket2_rect = dynamic_cast<Rectangle*>(rocket2->shape.get());
    Rectangle* cybertruck_rect = dynamic_cast<Rectangle*>(cybertruck->shape.get());
    Rectangle* rect = dynamic_cast<Rectangle*>(shape.get());
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifpath[{state,dir}]);
    //dir=HeroDir::LEFT;
    
    //std::cout<<"ok:"<<gifjump[{HeroDir::LEFT,"up"}]<<'\n';
    if (!rect) return;
    if(dash_redy)
        dash_timer=0;
    if(dash_redy && DC->key_state[ALLEGRO_KEY_SPACE]){
        if(DC->key_state[ALLEGRO_KEY_W])
            dir=HeroDir::UP;
        else if(DC->key_state[ALLEGRO_KEY_S])
            dir=HeroDir::DOWN;
        switch(dir){
            case HeroDir::UP:
                x_speed=0;
                y_speed=-dash_speed;
                dir=HeroDir::RIGHT;
                break;
            case HeroDir::DOWN:
                x_speed=0;
                y_speed=dash_speed;
                dir=HeroDir::RIGHT;
                break;
            case HeroDir::LEFT:
                x_speed=-dash_speed;
                y_speed=0;
                break;
            case HeroDir::RIGHT:
                x_speed=dash_speed;
                y_speed=0;
                break;
        }
        dash_control=true;
        dash_redy=false;
    }
    else if(!dash_redy){
        dash_timer++;
        if(dash_control && dash_timer>=dash_duration){
            dash_control=false;
            x_speed =0;
            y_speed =0;
        }
        if(dash_timer>=dash_duration*20){
            dash_redy=true;
        }
    }
    if(!dash_control){
        double jump_speed=std::max(max_jump_speed,max_jump_speed/2+abs(x_speed)*max_jump_speed/2/InTheAir::MAX_SPEED);
        if (jump_redy && DC->key_state[ALLEGRO_KEY_J] && !DC->prev_key_state[ALLEGRO_KEY_J] && jump_count < max_jump_limit) {
            if(dir == HeroDir::UP || dir == HeroDir::DOWN)
                dir=HeroDir::RIGHT;
            y_speed=jump_speed;
            jump_redy=false;
            jump_count++;
        }
        if(!jump_redy){
            jump_timer++;
            if(jump_timer>=jump_cooldown){
                jump_timer=0;
                jump_redy=true;
            }
        }
            
        if (DC->key_state[ALLEGRO_KEY_D]) {
            dir = HeroDir::RIGHT;
            if (state == HeroState::JUMP) {
                x_speed = (x_speed >= 0) ? std::min(x_speed + InTheAir::ACCELERATION, InTheAir::MAX_SPEED)
                                        : std::min(x_speed + InTheAir::TURN_ACCELERATION, InTheAir::MAX_SPEED);
            } else {
                x_speed = (x_speed >= 0) ? std::min(x_speed + OnTheGround::ACCELERATION, OnTheGround::MAX_SPEED)
                                        : std::min(x_speed + OnTheGround::TURN_ACCELERATION, OnTheGround::MAX_SPEED);
            }
        } else if (DC->key_state[ALLEGRO_KEY_A]) {
            dir = HeroDir::LEFT;
            if (state == HeroState::JUMP) {
                x_speed = (x_speed >=0) ? std::max(x_speed - InTheAir::TURN_ACCELERATION, -InTheAir::MAX_SPEED)
                                        : std::max(x_speed - InTheAir::ACCELERATION, -InTheAir::MAX_SPEED);
            } else {
                x_speed = (x_speed > 0) ? std::max(x_speed - OnTheGround::TURN_ACCELERATION, -OnTheGround::MAX_SPEED)
                                        : std::max(x_speed - OnTheGround::ACCELERATION, -OnTheGround::MAX_SPEED);
            }
        } else {
            // Decelerate if no key is pressed
            if (state == HeroState::JUMP) {
                if (x_speed > 0) {
                    x_speed = std::max(x_speed - InTheAir::DECELERATION, 0.0);
                    dir = HeroDir::RIGHT;
                } else if (x_speed < 0) {
                    x_speed = std::min(x_speed + InTheAir::DECELERATION, 0.0);
                    dir = HeroDir::LEFT;
                }
            } else {
                if (x_speed > 0) {
                    x_speed = std::max(x_speed - OnTheGround::DECELERATION, 0.0);
                    dir = HeroDir::RIGHT;
                } else if (x_speed < 0) {
                    x_speed = std::min(x_speed + OnTheGround::DECELERATION, 0.0);
                    dir = HeroDir::LEFT;
                }
            }
        }
    }
    if(rect->x2+x_speed>DC->window_width)
        rect->update_center_x(DC->window_width - (rect->x2 - rect->x1) / 2);
    else if(rect->x1+x_speed<0)
        rect->update_center_x((rect->x2 - rect->x1)/2);
    else
        rect->update_center_x(rect->center_x() + x_speed);
    if(rect->y1+y_speed<0){
        rect->update_center_y((rect->y2 - rect->y1)/2);
        y_speed=0;
    }
    else rect->update_center_y(rect->center_y() + y_speed);
    on_platform = false;
    hold=false;
    double x_buffer=platforms->get_block_width()/10;
    double y_buffer=platforms->get_block_height()/10;
    for (const auto& platform : platforms->get_platforms()) {
            CollisionType col=detectCollision(platform,platforms->get_block_width()/5);
            if(col!=CollisionType::None && platform.can_burn){
                (hp>1)?hero_injured = true:hero_died = true;
                return;
            }
            //std::cout<<"collip\n";
            switch(col){
                case CollisionType::Top:
                    rect->update_center_y(platform.y1 - (rect->y2 - rect->y1) / 2); 
                    if(platform.move_type == 7) 
                        y_speed=-bounding_factor*y_speed;
                    else 
                        y_speed = 0;    
                    on_platform = true;
                    jump_count = 0;
                    if(platform.can_move) current_platform = &platform;
                    else current_platform = nullptr;
                    //std::cout<<"TOP\n";
                    break;
                case CollisionType::Bottom:
                    rect->update_center_y(platform.y2 + (rect->y2 - rect->y1) / 2); 
                    if(platform.move_type == 7) 
                        y_speed=-bounding_factor*y_speed;
                    else 
                        y_speed = 0;      
                    //std::cout<<"BOTTOM\n";
                    break;
                case CollisionType::Left:
                    if(platform.can_hold && DC->key_state[ALLEGRO_KEY_K]){
                        dir=HeroDir::LEFT;
                        x_speed=-InTheAir::MAX_SPEED;
                        y_speed=climb_speed;
                    }
                    else if(platform.can_hold && DC->key_state[ALLEGRO_KEY_D]){
                        if(!DC->prev_key_state[ALLEGRO_KEY_D])
                            y_speed=0;
                        state=HeroState::HOLD;
                        rect->update_center_x(platform.x1-(rect->x2-rect->x1)/2);
                        x_speed=std::max(0.0, x_speed);
                        hold=true;
                        jump_count=std::min(jump_count+1,max_jump_limit);
                    }
                    if(platform.move_type == 7) 
                        x_speed=-bounding_factor*x_speed;
                    else{
                        x_speed=-x_speed/10;
                        rect->update_center_x(platform.x1-(rect->x2-rect->x1)/2);
                    }
                    
                    //std::cout<<"LEFT\n";
                    break;
                case CollisionType::Right:
                    if(platform.can_hold && DC->key_state[ALLEGRO_KEY_K]){
                        dir=HeroDir::RIGHT;
                        x_speed=InTheAir::MAX_SPEED;
                        y_speed=climb_speed;
                    }
                    else if(platform.can_hold && DC->key_state[ALLEGRO_KEY_A]){
                        if(!DC->prev_key_state[ALLEGRO_KEY_A])
                            y_speed=0;
                        state=HeroState::HOLD;
                        rect->update_center_x(platform.x2+(rect->x2-rect->x1)/2);
                        x_speed=std::max(0.0, x_speed);
                        hold=true;
                        jump_count=std::min(jump_count+1,max_jump_limit);
                    }
                    if(platform.move_type == 7) 
                        x_speed=-bounding_factor*x_speed;
                    else{
                        x_speed=-x_speed/10;
                        rect->update_center_x(platform.x2+(rect->x2-rect->x1)/2);
                    }
                    //std::cout<<"RIGHT\n";
                    break;
                default:
                    break;
            }
    }
    if(state == HeroState::HOLD){
        if(y_speed<0)
            y_speed+=down_gravity;
        else
            y_speed+=up_gravity/3;
    }
    else if(!on_platform){
        if(y_speed<0)
            y_speed+=up_gravity;
        else
            y_speed+=down_gravity;
        // std::cout<<y_speed<<std::endl;
    }
    if(rect->center_y()<=0){
        rect->update_center_y((rect->y2-rect->y1)/2);
    }
    if (!hold && !on_platform && rect->y2 < DC->window_height)
        state=HeroState::JUMP; 
    else if (!on_platform && rect->y1 >= DC->window_height && rect->center_x() >= die_x_start && rect->center_x() <= die_x_end){
        (hp>1)?hero_injured = true:hero_died = true;
    }
    if(!on_platform && rect->y1 >= DC->window_height && rect->center_x() >= die_x_end){
        teleport_to_earth2 = true;
    }
    if(rocket_rect && rocket_rect->y2 < 0){
        teleport_to_moon = true;
    }
    if(rocket2_rect && rocket2_rect->y2 < 0){
        teleport_to_mars = true;
    }
    if(cybertruck_rect && cybertruck_rect->x2 < 0){
        teleport_to_ending = true;
    }
    if(on_platform){
        if(std::abs(x_speed) <= 0.5){
            if(DC->key_state[ALLEGRO_KEY_W]) dir=HeroDir::UP;
            else if(DC->key_state[ALLEGRO_KEY_S]) dir=HeroDir::DOWN;
            state=HeroState::STOP; 
        }
        else{
            state=HeroState::RUN;
        }
    }

    if(DC->mouse_state[2]){
        rect->update_center_x(DC->mouse.x);
        rect->update_center_y(DC->mouse.y);
    }

    if (current_platform && (current_platform->move_type!=3 || current_platform->move_type!=4)){
        rect->update_center_x(rect->center_x() + current_platform->vx);
        rect->update_center_y(rect->center_y() + current_platform->vy);
    }

}
void Hero::draw(){
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif;
    gif=GIFC->get(heart_path);
    for(int i=0;i<hp;i++){
        algif_draw_gif(gif,i*gif->width+gif->width/2,gif->height/2,0);
    }
    if((dir == HeroDir::UP||dir == HeroDir::DOWN) && state!=HeroState::STOP)
        dir == HeroDir::RIGHT;
    if(dash_redy){
        if(state == HeroState::RUN || state == HeroState::STOP || state == HeroState::HOLD){
            gif = GIFC->get(gifpath[{state,dir}]);
        }
        else if(state == HeroState::JUMP && y_speed<0)
            gif = GIFC->get(gifjump[{dir,"up"}]);
        else 
            gif = GIFC->get(gifjump[{dir,"down"}]);
    }
    else{
        if(state == HeroState::RUN || state == HeroState::STOP || state == HeroState::HOLD){
            gif = GIFC->get(gif_dashpath[{state,dir}]);
        }
        else if(state == HeroState::JUMP && y_speed<0)
            gif = GIFC->get(gif_dashjump[{dir,"up"}]);
        else 
            gif = GIFC->get(gif_dashjump[{dir,"down"}]);
    }
    DataCenter* DC = DataCenter::get_instance(); 
    algif_draw_gif(gif, shape->center_x() - gif->width/2, shape->center_y()-gif->height/2, 0);    
    Rectangle* rect = dynamic_cast<Rectangle*>(shape.get()); 
    if (debug && rect){
        al_draw_rectangle(
            rect->x1, rect->y1, rect->x2, rect->y2,
            al_map_rgb(255, 0, 0), 
            2.0 
        );
        switch(state){
        case HeroState::JUMP:
            // std::cout<<"JUMP\n";
            break;
        case HeroState::RUN:
            // std::cout<<"RUN\n";
            break;
        case HeroState::STOP:
            // std::cout<<"STOP\n";
            break;
        }
        switch(dir){
            case HeroDir::LEFT:
                // std::cout<<"LEFT\n";
                break;
            case HeroDir::RIGHT:
                //std::cout<<"RIGHT\n";
                break;
            case HeroDir::UP:
                //std::cout<<"UP\n";
                break;
        }
        //std::cout<<"dash_redy:"<<(dash_redy)?1:0<<'\n';
        std::cout<< "x_speed = " <<x_speed<<" "<< "y_speed = " << y_speed<<" "<< "on_platform = " <<on_platform<<std::endl;
    }


}
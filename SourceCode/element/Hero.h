#ifndef Hero_H_INCLUDED
#define Hero_H_INCLUDED
#include "../algif5/algif.h"
#include "Object.h"
#include "../data/DataCenter.h"
#include "Platform.h"
#include "../Scene/Gamescene_earth.h"
#include "../Scene/Gamescene_earth_2.h"
#include "../Scene/Gamescene_moon.h"
#include "../Scene/Introduction.h"

enum class HeroState{
    RUN,STOP,JUMP,HOLD,MAX_STATE,HOLD_UP
};
enum class HeroDir{
    LEFT,RIGHT,MAX_DIR,UP,DOWN
};
enum class CollisionType{ 
    None, Top, Bottom, Left, Right 
};
namespace OnTheGround{
    constexpr double MAX_SPEED=10;
    constexpr double ACC_DURATION=0.516;
    constexpr double ACCELERATION=(MAX_SPEED/ACC_DURATION)/DataSetting::FPS;
    constexpr double DEC_DURATION=0.16;
    constexpr double DECELERATION=(MAX_SPEED/DEC_DURATION)/DataSetting::FPS;
    constexpr double TUR_DURATION=0.016;
    constexpr double TURN_ACCELERATION=(MAX_SPEED/TUR_DURATION)/DataSetting::FPS;
}
namespace InTheAir{
    constexpr double MAX_SPEED=10;
    constexpr double ACC_DURATION=0.257;
    constexpr double ACCELERATION=(MAX_SPEED/ACC_DURATION)/DataSetting::FPS;
    constexpr double DEC_DURATION=0.457;
    constexpr double DECELERATION=(MAX_SPEED/DEC_DURATION)/DataSetting::FPS;
    constexpr double TUR_DURATION=0.157;
    constexpr double TURN_ACCELERATION=(MAX_SPEED/TUR_DURATION)/DataSetting::FPS;
}
class Hero : public Object
{
public:
    Hero()=default;
    ~Hero()=default;
    void init();
    void update();
    void draw();
    CollisionType detectCollision(const Rectangle& platform,double collistion_buffer);
    const Hero& Get_Hero()const{return *this;}
    double &get_x_speed(){
        return x_speed;
    }
    double &get_y_speed(){
        return y_speed;
    }
    bool &up_dash(){
        return dash_redy;
    }
    friend class Gamescene_earth;
    friend class Gamescene_earth2;
    friend class Gamescene_moon;
    friend class Gamescene_mars;
    friend class Platform;
    friend class Introduction;
private:
    bool teleport_to_earth2 = false;
    bool teleport_to_moon = false;
    bool teleport_to_mars = false;
    bool teleport_to_ending = false;
    double die_x_start, die_x_end;
    double born_x1, born_y1, born_x2, born_y2;
    int hp;
    bool hero_injured;
    bool hero_died;
    int died_count = 0;
    double dash_duration;
    bool jump_redy;
    bool hold;
    bool on_platform;
    bool dash_redy;
    bool dash_control;
    double dash_length;
    double dash_speed;
	double x_speed,y_speed;
    HeroState state;
    HeroDir dir; 
    double max_jump_height;
    double max_jump_speed;
    int dash_timer;
    int jump_add_timer;
    int jump_timer;
    int jump_cooldown;
    const double down_gravity=0.6;
    const double up_gravity=0.3;
    int jump_count = 0;
    int hold_count=0;
    int max_jump_limit = 2;
    int max_hold_limit=1;
    int max_dash_limit=1;
    double climb_speed;
    double max_bvx;
    double max_bvy;
    double bounding=0;
    double bounding_factor=1.2;
    bool debug=true;
    bool gif_path_load=false;
    const Rectangle *current_platform = nullptr;
    std::map<std::pair<HeroState,HeroDir>,std::string>gifpath; //exclude jump
    std::map<std::pair<HeroDir,std::string>,std::string>gifjump; // jump
    std::map<std::pair<HeroState,HeroDir>,std::string>gif_dashpath;
    std::map<std::pair<HeroDir,std::string>,std::string>gif_dashjump; // jump
    std::string heart_path="./assets/gif/Hero/hero_heart.gif";
    ALGIF_ANIMATION *gif;
    CollisionType pre_col=CollisionType::Top;
};

#endif
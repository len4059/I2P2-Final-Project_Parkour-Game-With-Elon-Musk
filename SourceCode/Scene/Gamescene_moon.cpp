
#include "Gamescene_moon.h"
 
ALLEGRO_SAMPLE_INSTANCE *Gamescene_moon::background_music = nullptr;

Gamescene_moon::Gamescene_moon(){
    init();
}

Gamescene_moon::~Gamescene_moon() {
    destroy();
}

void Gamescene_moon::init() {
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

	Platform *PLT=DC->platforms;

	SC->init();
	FC->init();
	RectangleParams move_block_x1 = {1,true, false, true, false, 2.0, 0.0,72.0,792.0};
	RectangleParams fire_move_block_y1 = {3,true, true, true, true, 0.0, 8.0,600.0,825.0,-9.0,Detect_side::LORAD};
	RectangleParams fire_move_block_x1 = {4,true,false,true,true,3.0,0.0,1008.0,1368.0,-10.0,Detect_side::UODAR};
	RectangleParams move_block_x2 = {1,true,false,true,false,1.0,0.0,1224.0,1440.0};
	RectangleParams move_block_y3 = {2,true,false,true,true,0,2.0,0.0,300.0};
	RectangleParams fire_move_block_x2 = {1,true, true, true, true, 3.0, 0.0,144.0,792.0};
    //Load the background
    background_img = IC->get(Resource::moon_background_img_path);
	moon_wall = IC->get(Resource::moon_wall);
	moon_land = IC->get(Resource::moon_land);
	moon_ice = IC->get(Resource::moon_ice);
	moon_fire = IC->get(Resource::fire_block);
	mode[1]=fire_move_block_y1;
	mode[2]=fire_block;
	mode[3]=fire_move_block_x1;
	mode[4]=normal_block;
	mode[5]=invisible_block;
	mode[6]=move_block_x2;
	mode[7]=ice_block;
	mode[8]=move_block_x1;
	mode[9]=move_block_y3;
	DC->platforms->loadmap(Resource::map_moon, mode,DC->window_width, DC->window_height);
	DC->platforms->textures[1] = moon_fire;
	DC->platforms->textures[2] = moon_fire;
	DC->platforms->textures[3] = moon_fire;
	DC->platforms->textures[4] = moon_land;
 	DC->platforms->textures[5] = moon_wall;   // invisible block
	DC->platforms->textures[6] = moon_wall;
	DC->platforms->textures[7] = moon_ice;
	DC->platforms->textures[8] = moon_wall;
	DC->platforms->textures[9] = moon_fire;
	DC->hero->init();
	hero_init();

	// Initialize other elements
    DC->platforms->init();
	DC->rocket2->init();

	button_width = 200;
	button_height = 90;
	pause_menu_button_x = pause_tryagain_button_x = (DC->window_width - button_width) / 2;
	pause_tryagain_button_y = DC->window_height / 2;
	pause_menu_button_y = pause_tryagain_button_y + 150;
	button_color = al_map_rgb(255, 180, 100);
	button_hover_color = al_map_rgb(255, 230, 150);  

	DC->hero->teleport_to_mars = false;
	state = STATE::PLAYING;
	Gamescene_moon::BGM_played = true;
}

bool Gamescene_moon::update() {
	DataCenter *DC = DataCenter::get_instance();
	OperationCenter *OC = OperationCenter::get_instance();
	SoundCenter *SC = SoundCenter::get_instance();

	if(BGM_played){
		background_music = SC->play(Resource::moon_bgm, ALLEGRO_PLAYMODE_LOOP);
		BGM_played = false;
	}

	if (DC->key_state[ALLEGRO_KEY_ESCAPE] && !DC->prev_key_state[ALLEGRO_KEY_ESCAPE]) {
        if (state == STATE::PLAYING) {
			SC->toggle_playing(background_music);
            state = STATE::PAUSE; 
			BGM_played = false;
        } else if (state == STATE::PAUSE) {
            state = STATE::PLAYING; 
			BGM_played = true;
        }
    }

	if(state == STATE::PLAYING){
		DC->hero->update();

		DC->platforms->update();

		DC->rocket2->update();

		OC->update();
		// game_update is finished. The states of current frame will be previous states of the next frame.
		if(DC->hero->hero_injured){
			DC->hero->init();
			hero_init();
			DC->hero->died_count++;
			DC->hero->hp = 3-DC->hero->died_count;
		}
		else if(DC->hero->hero_died){
			DC->hero->died_count = 0;
			std::cout << "Fail" << std::endl;
			SC->stop_playing(background_music);
			window = Scenetype::Fail;
			return false;
		}
	}

	if(state == STATE::PAUSE){
		if (DC->mouse_state[1] &&
			DC->mouse.x >= pause_menu_button_x && DC->mouse.x <= pause_menu_button_x + button_width &&
			DC->mouse.y >= pause_menu_button_y && DC->mouse.y <= pause_menu_button_y + button_height) {
			std::cout << "switch to menu" << std::endl;
			SC->stop_playing(background_music);
			window = Scenetype::Menu;  
			DC->hero->died_count = 0;
			return false;
		}

		if (DC->mouse_state[1] &&
			DC->mouse.x >= pause_tryagain_button_x && DC->mouse.x <= pause_tryagain_button_x + button_width &&
			DC->mouse.y >= pause_tryagain_button_y && DC->mouse.y <= pause_tryagain_button_y + button_height) {
			std::cout << "Try Again" << std::endl;
			DC->hero->init();
            hero_init();
            state = STATE::PLAYING;
			BGM_played = true;
			DC->hero->died_count = 0;
            return true;
		}
	}
	
	if(DC->hero->teleport_to_mars){
		DC->hero->died_count = 0;
		SC->stop_playing(background_music);
		window = Scenetype::moon_to_mars;
		DC->hero->teleport_to_mars = false;
		std::cout << "Switching to Gamescene_mars" << std::endl;
		return false;
	}

	// std::cout << " teleport_to_mars: " << DC->hero->teleport_to_mars << std::endl;

	memcpy(DC->prev_key_state, DC->key_state, sizeof(DC->key_state));
	memcpy(DC->prev_mouse_state, DC->mouse_state, sizeof(DC->mouse_state));
	return true;
}

void Gamescene_moon::draw(){
	DataCenter *DC = DataCenter::get_instance();
	OperationCenter *OC = OperationCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();
	Rocket2* rocket2 = DC->rocket2;
	//Flush the screen first.
	al_clear_to_color(al_map_rgb(100, 100, 100));
	// background
	al_draw_bitmap(background_img, 0, 0, 0);
	OC->draw();
	DC->rocket2->draw();
	if(!rocket2->isgoing_up) DC->hero->draw();
	DC->platforms->draw();
	switch(state) {
		case STATE::PLAYING:{
			break;
		}
		case STATE::PAUSE: {

			al_draw_filled_rectangle(0, 0, DC->window_width, DC->window_height, al_map_rgba(50, 50, 50, 64));
			al_draw_text(
				FC->caviar_dreams[FontSize::LARGE], al_map_rgb(255, 255, 255),
				DC->window_width / 2., DC->window_height / 2. - 150,
				ALLEGRO_ALIGN_CENTRE, "GAME PAUSED");

			ALLEGRO_COLOR menu_color = button_color;
			if (DC->mouse.x >= pause_menu_button_x && DC->mouse.x <= pause_menu_button_x + button_width &&
				DC->mouse.y >= pause_menu_button_y && DC->mouse.y <= pause_menu_button_y + button_height) {
				menu_color = button_hover_color; 
			}
			al_draw_filled_rectangle(
				pause_menu_button_x, pause_menu_button_y,
				pause_menu_button_x + button_width, pause_menu_button_y + button_height,
				menu_color);
			al_draw_rectangle(
				pause_menu_button_x, pause_menu_button_y,
				pause_menu_button_x + button_width, pause_menu_button_y + button_height,
				al_map_rgb(0, 0, 0), 2.0); 
			al_draw_text(
				FC->caviar_dreams[FontSize::MEDIUM], al_map_rgb(0, 0, 0),
				pause_menu_button_x + button_width / 2,
				pause_menu_button_y + (button_height - al_get_font_line_height(FC->caviar_dreams[FontSize::MEDIUM])) / 2,
				ALLEGRO_ALIGN_CENTRE, "MENU");

			ALLEGRO_COLOR tryagain_color = button_color;
			if (DC->mouse.x >= pause_tryagain_button_x && DC->mouse.x <= pause_tryagain_button_x + button_width &&
				DC->mouse.y >= pause_tryagain_button_y && DC->mouse.y <= pause_tryagain_button_y + button_height) {
				tryagain_color = button_hover_color; 
			}
			al_draw_filled_rectangle(
				pause_tryagain_button_x, pause_tryagain_button_y,
				pause_tryagain_button_x + button_width, pause_tryagain_button_y + button_height,
				tryagain_color);
			al_draw_rectangle(
				pause_tryagain_button_x, pause_tryagain_button_y,
				pause_tryagain_button_x + button_width, pause_tryagain_button_y + button_height,
				al_map_rgb(0, 0, 0), 2.0);
			al_draw_text(
				FC->caviar_dreams[FontSize::MEDIUM], al_map_rgb(0, 0, 0),
				pause_tryagain_button_x + button_width / 2,
				pause_tryagain_button_y + (button_height - al_get_font_line_height(FC->caviar_dreams[FontSize::MEDIUM])) / 2,
				ALLEGRO_ALIGN_CENTRE, "TRY AGAIN");
			break;
		}
		case STATE::END:{
			break;
		}
	}
}


void Gamescene_moon::destroy() {
	if(background_img) background_img = nullptr;
	if(background_music) background_music = nullptr;
    std::cout << "gamescene_earth destroy" << std::endl;
}

void Gamescene_moon::hero_init(){
	DataCenter *DC = DataCenter::get_instance();
	Platform *PLT=DC->platforms;
	DC->hero->hero_died = false;
	DC->hero->dash_length = PLT->get_block_height();
	DC->hero->dash_duration = 0.1*DC->FPS;
	DC->hero->max_jump_height = PLT->get_block_height()*3;
	DC->hero->max_jump_speed = -std::sqrt(1.5*DC->hero->up_gravity * DC->hero->max_jump_height);
	DC->hero->climb_speed = DC->hero->max_jump_speed/1.82;
}

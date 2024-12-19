#include "Gamescene_mars.h"

ALLEGRO_SAMPLE_INSTANCE *Gamescene_mars::background_music = nullptr;

Gamescene_mars::Gamescene_mars(){
    init();
}

Gamescene_mars::~Gamescene_mars() {
    destroy();
}

void Gamescene_mars::init() {
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

	Platform *PLT=DC->platforms;

	SC->init();
	FC->init();
	RectangleParams move_block_1 = {1,true,true,true,false,1.0, 0.0, DC->window_width/20*10, DC->window_width/20*16};
	RectangleParams bounding_block={7,false,true,true,false};
	RectangleParams gravity_block_up1={8,true,true,true,false,0.0,-0.8,0.0,0.0,125.0,Detect_side::GU};
	RectangleParams gravity_block_down1={8,true,true,true,false,0.0,0.1,0.0,0.0,125.0,Detect_side::GD};
	RectangleParams gravity_block_left1={8,true,true,true,false,-9.0,0.0,0.0,0.0,360.0,Detect_side::GR};
	RectangleParams gravity_block_right2={8,true,true,true,false,-3.0,0.0,0.0,0.0,576.0,Detect_side::GR};
    //Load the background
    //Load the background
    background_img = IC->get(Resource::mars_background_img_path);
	mars_wall = IC->get(Resource::moon_wall);
	mars_land = IC->get(Resource::earth_land);
	mars_mud = IC->get(Resource::earth_mud);
	mars_ice = IC->get(Resource::moon_ice);
	mars_cloud = IC->get(Resource::earth_cloud);
	mars_bird = IC->get(Resource::earth_bird);
	mars_fire = IC->get(Resource::fire_block);
	mars_bounding_block=IC->get(Resource::bounding_block);
	mode[1]=ice_block;
	mode[2]=fire_block;
	mode[3]=bounding_block;
	mode[4]=gravity_block_up1;
	mode[5]=gravity_block_left1;
	mode[6]=gravity_block_down1;
	mode[8]=move_block_1;
	mode[9]=normal_block;
	DC->platforms->loadmap(Resource::map_mars,mode,DC->window_width, DC->window_height);
	
	DC->platforms->textures[1] = mars_mud;
	DC->platforms->textures[2] = mars_fire;
	DC->platforms->textures[3] = mars_bounding_block;
	DC->platforms->textures[4] = mars_land;
	DC->platforms->textures[5] = mars_wall;
	DC->platforms->textures[6] = mars_wall;
	DC->platforms->textures[8] = mars_bird;
	DC->platforms->textures[9] = mars_land;

	// Initialize other elements
    DC->platforms->init();
	DC->hero->init();
	hero_init();
	DC->energy->init();
    DC->cybertruck->init();

	button_width = 200;
	button_height = 90;
	pause_menu_button_x = pause_tryagain_button_x = (DC->window_width - button_width) / 2;
	pause_tryagain_button_y = DC->window_height / 2;
	pause_menu_button_y = pause_tryagain_button_y + 150;
	button_color = al_map_rgb(255, 180, 100);
	button_hover_color = al_map_rgb(255, 230, 150);  

    DC->hero->teleport_to_ending = false;

	state = STATE::PLAYING;

	Gamescene_mars::BGM_played = true;
}


bool Gamescene_mars::update() {
	DataCenter *DC = DataCenter::get_instance();
	OperationCenter *OC = OperationCenter::get_instance();
	SoundCenter *SC = SoundCenter::get_instance();

	if(BGM_played){
		background_music = SC->play(Resource::earth_background_music, ALLEGRO_PLAYMODE_LOOP);
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
		DC->energy->update();
        DC->cybertruck->update();
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
		else if(DC->key_state[ALLEGRO_KEY_1]){
			SC->stop_playing(background_music);
			window = Scenetype::Game_moon;
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

    if(DC->hero->teleport_to_ending){
		DC->hero->died_count = 0;
		SC->stop_playing(background_music);
		window = Scenetype::Ending;
		DC->hero->teleport_to_ending = false;
		return false;
	}
	
	memcpy(DC->prev_key_state, DC->key_state, sizeof(DC->key_state));
	memcpy(DC->prev_mouse_state, DC->mouse_state, sizeof(DC->mouse_state));

	return true;
}

void Gamescene_mars::draw(){
	DataCenter *DC = DataCenter::get_instance();
	OperationCenter *OC = OperationCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();
    Cybertruck *cybertruck = DC->cybertruck;
	//Flush the screen first.
	al_clear_to_color(al_map_rgb(100, 100, 100));
	// background
	al_draw_bitmap(background_img, 0, 0, 0);

	OC->draw();
	DC->platforms->draw();
	DC->energy->draw();
    DC->cybertruck->draw();
	if(!cybertruck->isgoing_up) DC->hero->draw();
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


void Gamescene_mars::destroy() {

	if(background_img) background_img = nullptr;
	if(background_music) background_music = nullptr;
	
    std::cout << "gamescene_mars destroy" << std::endl;
}

void Gamescene_mars::hero_init(){
	DataCenter *DC = DataCenter::get_instance();
	Platform *PLT=DC->platforms;
	DC->hero->hero_died = false;
	DC->hero->dash_length = PLT->get_block_height();
	double spawn_x =108;
	double spawn_y =750;
	Rectangle* rect = dynamic_cast<Rectangle*>(DC->hero->shape.get());
    if (rect) {
        rect->update_center_x(spawn_x);
        rect->update_center_y(spawn_y);
    }
	DC->hero->dash_duration = 0.1*DC->FPS;
	DC->hero->max_jump_height = PLT->get_block_height()*3;
	DC->hero->max_jump_speed = -std::sqrt(1.5*DC->hero->up_gravity * DC->hero->max_jump_height);
	DC->hero->climb_speed = DC->hero->max_jump_speed/1.82;
}
#include "GameWindow.h"
#include "Utils.h"
#include "Global.h"
#include "shapes/Shape.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <cstring>
#include <iostream>

#include "element/Hero.h"
#include "element/Platform.h"

/**
 * @brief Initialize all allegro addons and the game body.
 * @details Only one timer is created since a game and all its data should be processed synchronously.
 */
Game::Game() {
	// std::cout << "in gamewindow constuctor" << std::endl;
	game_init();
}

Game::~Game() {
	// std::cout << "in gamewindow distructor" << std::endl;
	game_destroy();
}

/**
 * @brief Game entry.
 * @details The function processes all allegro events and update the event state to a generic data storage (i.e. DataCenter).
 * For timer event, the game_update and game_draw function will be called if and only if the current is timer.
 */

void Game::execute() {
	DataCenter *DC = DataCenter::get_instance();
	// main game loop
	bool run = true;
	if(!run) std::cout << "gamewindow game_update fail" << std::endl;
	while(run) {
		// process all events here
		al_wait_for_event(event_queue, &event);
		// std::cout << "in gamewindow execute" << std::endl;
		// if(event.type) std::cout << "gamewindow event.type success" << std::endl;
		switch(event.type) {
			case ALLEGRO_EVENT_TIMER: {
				run &= game_update();
				game_draw();
				break;
			} case ALLEGRO_EVENT_DISPLAY_CLOSE: { // stop game
			// std::cout << "gamewindow execute run false" << std::endl;
				run = false;
				break;
			} case ALLEGRO_EVENT_KEY_DOWN: {
				DC->key_state[event.keyboard.keycode] = true;
				break;
			} case ALLEGRO_EVENT_KEY_UP: {
				DC->key_state[event.keyboard.keycode] = false;
				break;
			} case ALLEGRO_EVENT_MOUSE_AXES: {
				DC->mouse.x = event.mouse.x;
				DC->mouse.y = event.mouse.y;
				break;
			} case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
				DC->mouse_state[event.mouse.button] = true;
				break;
			} case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
				DC->mouse_state[event.mouse.button] = false;
				break;
			} default: break;
		}
	}
	// std::cout << "gamewindow executed" << std::endl; 
}

/**
 * @brief Initialize all auxiliary resources.
 */
void
Game::game_init() {
	// std::cout << "in gamewindow init" << std::endl;
	DataCenter *DC = DataCenter::get_instance();
	SoundCenter *SC = SoundCenter::get_instance();
	ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

	GAME_ASSERT(al_init(), "failed to initialize allegro.");

	// initialize allegro addons
	bool addon_init = true;
	addon_init &= al_init_primitives_addon();
	addon_init &= al_init_font_addon();
	addon_init &= al_init_ttf_addon();
	addon_init &= al_init_image_addon();
	addon_init &= al_init_acodec_addon();
	GAME_ASSERT(addon_init, "failed to initialize allegro addons.");

	// initialize events
	bool event_init = true;
	event_init &= al_install_keyboard();
	event_init &= al_install_mouse();
	event_init &= al_install_audio();
	GAME_ASSERT(event_init, "failed to initialize allegro events.");

	GAME_ASSERT(al_reserve_samples(10), "Failed to reserve audio samples.");

	// initialize game body
	GAME_ASSERT(
		display = al_create_display(DC->window_width, DC->window_height),
		"failed to create display.");
	GAME_ASSERT(
		timer = al_create_timer(1.0 / DC->FPS),
		"failed to create timer.");
	GAME_ASSERT(
		event_queue = al_create_event_queue(),
		"failed to create event queue.");

	game_icon = IC->get(Resource::game_icon);
	al_set_display_icon(display, game_icon);

	std::cout << "event queue" << std::endl;
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
	std::cout << "event queue finish" << std::endl;

	SC->init();
	FC->init();

	background = IC->get(Resource::earth_background_img_path);

	std::cout << "icon success" << std::endl;

	scenemanager = new Scenemanager();

	al_start_timer(timer);

	debug_log("Gamewindow initialized.\n");
}

/**
 * @brief The function processes all data update.
 * @details The behavior of the whole game body is determined by its state.
 * @return Whether the game should keep running (true) or reaches the termination criteria (false).
 * @see Game::STATE
 */

bool Game::game_update() {
    static Scenetype previous_scene = Scenetype::Leave;

    if (window != previous_scene) {
        scenemanager->Create_Scene(window);
        previous_scene = window;
    }

    if (!scenemanager->update_Scene()) {
        return false;  
    }

	if(window == Scenetype::Leave) game_destroy();

    return true;  
}



/**
 * @brief Draw the whole game and objects.
 */
void Game::game_draw() {
	// std::cout << "in gamewindow draw" << std::endl;
	scenemanager->draw_Scene();
	al_flip_display();
}

void Game::game_destroy(){

    if (event_queue) al_destroy_event_queue(event_queue);
    if (timer) al_destroy_timer(timer);
    if (display) al_destroy_display(display);

	debug_log("Gamewindow destroyed.");
}
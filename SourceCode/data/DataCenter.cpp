#include "DataCenter.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include "../Level.h"
#include "../Player.h"
#include "../monsters/Monster.h"
#include "../towers/Tower.h"
#include "../towers/Bullet.h"
// fixed settings


DataCenter::DataCenter() {
	this->FPS = DataSetting::FPS;
	this->window_width = DataSetting::window_width;
	this->window_height = DataSetting::window_height;
	this->game_field_length = DataSetting::game_field_length;
	memset(key_state, false, sizeof(key_state));
	memset(prev_key_state, false, sizeof(prev_key_state));
	mouse = Point(0, 0);
	memset(mouse_state, false, sizeof(mouse_state));
	memset(prev_mouse_state, false, sizeof(prev_mouse_state));
	// player = new Player();
	// level = new Level();
	
	hero = new Hero();
	platforms = new Platform();
	glasses = new Glasses();
	rocket = new Rocket();
	rocket2 = new Rocket2();
	energy = new Energy();	
	cybertruck = new Cybertruck();
}

DataCenter::~DataCenter() {
	// delete player;
	// delete level;
	// for(Monster *&m : monsters) {
	// 	delete m;
	// }
	// for(Tower *&t : towers) {
	// 	delete t;
	// }
	// for(Bullet *&b : towerBullets) {
	// 	delete b;
	// }
	delete hero;
	delete platforms;
	delete glasses;
	delete rocket;
	delete rocket2;
	delete energy;
	delete cybertruck;
}
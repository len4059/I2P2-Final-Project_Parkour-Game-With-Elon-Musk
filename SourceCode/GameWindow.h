#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include <allegro5/allegro.h>

#include "data/DataCenter.h"
#include "data/OperationCenter.h"
#include "data/SoundCenter.h"
#include "data/ImageCenter.h"
#include "data/FontCenter.h"

#include "UI.h"
#include "Scene/Scenemanager.h"
#include "Resource.h"

/**
 * @brief Main class that runs the whole game.
 * @details All game procedures must be processed through this class.
 */

class DataCenter;
class SoundCenter;
class ImageCenter;
class FontCenter;

class Game
{
public:
	void execute();
public:
	Game();
	~Game();
	void game_init();
	bool game_update();
	void game_draw();
	void game_destroy();
private:
	/**
	 * @brief States of the game process in game_update.
	 * @see Game::game_update()
	 */
	enum class STATE {
		START, // -> LEVEL
		LEVEL, // -> PAUSE, END
		PAUSE, // -> LEVEL
		END
	};
	STATE state;
	ALLEGRO_BITMAP *game_icon;
	ALLEGRO_BITMAP *background;
private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_TIMER *timer;

	Scenemanager *scenemanager;
};

#endif

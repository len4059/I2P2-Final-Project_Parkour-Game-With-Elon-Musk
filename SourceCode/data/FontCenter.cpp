#include "FontCenter.h"
#include <allegro5/allegro.h> 
#include <allegro5/allegro_ttf.h>

#include <iostream>

// fixed settings
namespace FontSetting {
	constexpr char caviar_dreams_font_path[] = "assets/font/Caviar_Dreams_Bold.ttf";
	constexpr char courier_new_font_path[] = "assets/font/courbd.ttf";
}


void FontCenter::init() {
    std::cout << "Initializing fonts..." << std::endl;

    for(const int &fs : FontSize::list) {
        ALLEGRO_FONT* font1 = al_load_ttf_font(FontSetting::caviar_dreams_font_path, fs, 0);
        if (!font1) {
            std::cerr << "Failed to load font: " << FontSetting::caviar_dreams_font_path 
                      << " with size " << fs << std::endl;
            std::cerr << "Current working directory: " << al_get_current_directory() << std::endl;
            exit(EXIT_FAILURE);
        }
        caviar_dreams[fs] = font1;

        ALLEGRO_FONT* font2 = al_load_ttf_font(FontSetting::courier_new_font_path, fs, 0);
        if (!font2) {
            std::cerr << "Failed to load font: " << FontSetting::courier_new_font_path 
                      << " with size " << fs << std::endl;
            std::cerr << "Current working directory: " << al_get_current_directory() << std::endl;
            exit(EXIT_FAILURE);
        }
        courier_new[fs] = font2;
    }
    std::cout << "Fonts initialized successfully." << std::endl;
}


FontCenter::~FontCenter() {
	for(auto &[size, font] : caviar_dreams)
		al_destroy_font(font);
	for(auto &[size, font] : courier_new)
		al_destroy_font(font);
}

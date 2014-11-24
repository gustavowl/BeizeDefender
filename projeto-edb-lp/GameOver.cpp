#include <allegro5/allegro.h> 
#include <allegro5/allegro_image.h>
#include "GameOver.h"


GameOver::GameOver()
{}

int GameOver::Executar( ALLEGRO_DISPLAY *display )
{

	ALLEGRO_BITMAP *game_over = NULL;

	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	game_over = al_load_bitmap("Menu/GameOver.png");
	al_draw_bitmap(game_over, 0, 0, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	al_rest(3);
	al_destroy_bitmap(game_over);

	return 0;
}
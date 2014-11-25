#include <allegro5/allegro.h> 
#include <allegro5/allegro_image.h>
#include "Victory.h"


Victory::Victory()
{}

Victory::~Victory()
{}

int Victory::Executar( ALLEGRO_DISPLAY *display )
{

	ALLEGRO_BITMAP *victory = NULL;

	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	victory = al_load_bitmap("Menu/Win.png");
	al_draw_bitmap(victory, 0, 0, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	al_rest(3);
	al_destroy_bitmap(victory);

	return 3;
}
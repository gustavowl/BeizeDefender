#include <iostream>

#include <allegro5/allegro.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "Creditos.h"


Creditos::Creditos()
{}

Creditos::~Creditos()
{}

void Creditos::checkExpression(bool expression, std::string message)
{
	if (expression) {
		std::cout << message << std::endl;
		exit(1);
	}
}

int Creditos::Executar( ALLEGRO_DISPLAY *display )
{

	ALLEGRO_AUDIO_STREAM * trilha = NULL;
	bool done = true;

	checkExpression(!al_install_audio(), "Problemas ao iniciar o plugin de audio. Abortar!");
	checkExpression(!al_init_acodec_addon(), "Problemas ao iniciar o plugin adicional de audio. Abortar!");


	trilha = al_load_audio_stream("Music/RGF.wav", 5, 1024);
	checkExpression(!trilha, "Música não Carregada");

	al_reserve_samples(1);
	al_attach_audio_stream_to_mixer(trilha, al_get_default_mixer());
	al_set_audio_stream_playmode(trilha, ALLEGRO_PLAYMODE_ONCE);

	ALLEGRO_BITMAP *creditos = NULL;
	ALLEGRO_BITMAP *creditos1 = NULL;
	ALLEGRO_BITMAP *creditos2 = NULL;
	ALLEGRO_BITMAP *creditos3 = NULL;
	ALLEGRO_BITMAP *creditos4 = NULL;
	ALLEGRO_BITMAP *creditos5 = NULL;
	ALLEGRO_BITMAP *creditos6 = NULL;


	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));



	creditos = al_load_bitmap("Creditos/creditos.png");
	checkExpression(!al_load_bitmap("Creditos/creditos.png"), "Problemas ao carregar a imagem. Abortar!");

	al_draw_bitmap(creditos, 0, 0, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	al_rest(3);
	al_destroy_bitmap(creditos);

	creditos1 = al_load_bitmap("Creditos/creditos1.png");
	checkExpression(!al_load_bitmap("Creditos/creditos1.png"), "Problemas ao carregar a imagem. Abortar!");

	al_draw_bitmap(creditos1, 0, 0, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	al_rest(4);
	al_destroy_bitmap(creditos1);

	creditos2 = al_load_bitmap("Creditos/creditos2.png");
	checkExpression(!al_load_bitmap("Creditos/creditos2.png"), "Problemas ao carregar a imagem. Abortar!");

	al_draw_bitmap(creditos2, 0, 0, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	al_rest(4);
	al_destroy_bitmap(creditos2);


	creditos3 = al_load_bitmap("Creditos/creditos3.png");
	checkExpression(!al_load_bitmap("Creditos/creditos3.png"), "Problemas ao carregar a imagem. Abortar!");

	al_draw_bitmap(creditos3, 0, 0, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	al_rest(6);
	al_destroy_bitmap(creditos3);

	creditos4 = al_load_bitmap("Creditos/creditos4.png");
	checkExpression(!al_load_bitmap("Creditos/creditos4.png"), "Problemas ao carregar a imagem. Abortar!");

	al_draw_bitmap(creditos4, 0, 0, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	al_rest(4);
	al_destroy_bitmap(creditos4);


	creditos5 = al_load_bitmap("Creditos/creditos5.png");
	checkExpression(!al_load_bitmap("Creditos/creditos5.png"), "Problemas ao carregar a imagem. Abortar!");

	al_draw_bitmap(creditos5, 0, 0, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	al_rest(7);
	al_destroy_bitmap(creditos5);

	creditos6 = al_load_bitmap("Creditos/creditos6.png");
	checkExpression(!al_load_bitmap("Creditos/creditos6.png"), "Problemas ao carregar a imagem. Abortar!");

	al_draw_bitmap(creditos5, 0, 0, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	al_rest(3);
	al_destroy_bitmap(creditos5);

	al_destroy_audio_stream(trilha);

	return 0;
}
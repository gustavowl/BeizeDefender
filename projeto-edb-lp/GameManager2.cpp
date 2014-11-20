#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <cstdlib>
#include <math.h>
#include "GameObject.h"
#include "ListaEncadeada/lista.h"
#include "Projetil.h"
#include "Base.h"
#include "Player.h"
#include "Inimigo.h"
#include "Horda.h"
#include "Waves.h"

using namespace go;

int main() {
    int i, X, Y, fps = 30;
    float v, qtd_ite = 0;
    bool done = false;

	GameObject arena(1024, 640);
	Base base(380, 200, 620, 440);
	Projetil proj_player(0, 0, 30, 1, 1, 2, 5);
	Player player(base.GetXAtual() , base.GetYAtual() , 50, 25, 15, 100, 10, proj_player);
	Projetil proj_inimigo(0, 0, 30, 1, 1, 2, 1);
	Lista<Horda*> fila_horda(FILA);
	Lista<int> fila_tempo_espera(FILA);

	//gera horda para wave
	for (int i = 2; i <= 6; i+=2) {
		Horda* nova_horda = new Horda(i, 2, 5, 10, 10, 30, 60, proj_inimigo);
		fila_horda.Insert( nova_horda );
		fila_tempo_espera.Insert( i * 15 ); //espera 1, 2 e 3 segundos
	}
	//gera wave
	Waves wave( fila_horda, fila_tempo_espera );

	//variaveis do allegro


	if( !al_init() )
		return -1;

	ALLEGRO_BITMAP *background = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	
	timer = al_create_timer(1.0 / fps);
	if (!timer)
		return -1;

	display = al_create_display( (int)arena.GetMaxX(), (int)arena.GetMaxY() );

	if (!display) {
		al_destroy_timer(timer);
		return -1;
	}

	//background = al_create_bitmap(1024,640);
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_destroy_timer(timer);
		al_destroy_display(display);
		return -1;
	}

	if ( !al_install_mouse() ) {
		al_destroy_event_queue(event_queue);
		al_destroy_timer(timer);
		al_destroy_display(display);
		return -1;
	}

	al_init_image_addon();

	al_init_font_addon();
	
	if(!al_load_bitmap("base_concept.png")) {
		std::cout << "Image not loaded" << std::endl;
		return -1;
	}
	if(!al_init_ttf_addon()) {
		std::cout << "Font not loaded" << std::endl;

		return -1;
	}



	background = al_load_bitmap("base_concept.png");
	font = al_load_font("WEST.TTF", 48, 0);

	if(!font) 
	{
		al_destroy_display(display);
		return -1;
	}



	//al_init_primitives_addon();	

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);

	ALLEGRO_EVENT ev;
	srand(time(NULL));
	while(!done)
	{

		if ( al_get_next_event(event_queue, &ev) ) {
		  //if (al_wait_for_event_until(event_queue, &ev, &timeout)) {

			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{	
				done = true;
			}
			//verifica se o jogo não acabou
			else if ( player.GetVida() > 0 && base.GetVida() > 0 && !wave.Destruida() ) {
				if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{

					if(ev.mouse.button & 2) {
	          			player.AtualizarDestino(ev.mouse.x, ev.mouse.y);
					}
					
					else if(ev.mouse.button & 1)
					{
	          			player.Atirar(ev.mouse.x, ev.mouse.y); //oks

					}
				}
				else if (ev.type == ALLEGRO_EVENT_TIMER) {
					player.Mover(); //já move os projéteis do player
					wave.Mover(player, base); //move projéteis da wave, msm se horda destruída (?)
					if ( !wave.EsperandoProximaHorda() ) {
						//só atira caso horda não tenha sido destruída
						wave.Atirar(player, base);
						//verifica dano nos inimigos da horda
						wave.VerificarColisaoProjPersInim(player);
					}
					player.LevarDano( wave.VerificarColisaoProjInimObj(player) );
					//dano colocado antes do desenho para dar a ilusão de maior tamanho da base
					base.LevarDano( wave.VerificarColisaoProjInimObj(base) );

					base.Draw();
					al_draw_bitmap(background, 0, 0, 0);

					player.Draw();

					wave.Draw();
					al_draw_textf(font, al_map_rgb(0, 0, 200), 1024, 0, ALLEGRO_ALIGN_RIGHT, "Vida: %d", player.GetVida());
					al_draw_textf(font, al_map_rgb(0, 0, 200), 1024, 50, ALLEGRO_ALIGN_RIGHT, "Base: %d", base.GetVida());
					al_draw_textf(font, al_map_rgb(0, 0, 200), 1024, 100, ALLEGRO_ALIGN_RIGHT, "Energia: %d", player.GetMunicaoAtual());


					al_flip_display();
					al_clear_to_color(al_map_rgb(0,0,0));					
				}
			}
		}
	}
	
	al_uninstall_mouse();
	al_destroy_bitmap(background);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_uninstall_system();
	return 0;
}
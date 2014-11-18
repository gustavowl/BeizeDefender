#include <iostream>
#include <allegro5/allegro.h>
#include <math.h>
#include "GameObject.h"
#include "ListaEncadeada/lista.h"
#include "Projetil.h"
#include "Base.h"
#include "Player.h"
#include "Inimigo.h"
#include "Horda.h"

using namespace go;

GameObject arena(1024, 640); 
Player player(1024/2, 640/2, 50, 50, 100);
Base base(380,200,620,440);
Horda horda(5, 1);

int main() {
    int i, X, Y, fps = 30;
    float v, qtd_ite = 0;
    bool done = false;

	//variaveis do allegro


	if( !al_init() )
		return -1;

	ALLEGRO_TIMER *timer = NULL;
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
			else if ( player.GetVida() > 0 && base.GetVida() > 0 && !horda.Destruida() ) {
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
					horda.Mover(player, base.GetRaio());
					horda.Atirar(player);
					player.LevarDano( horda.VerificarColisaoProjInimObj(player) );
					horda.VerificarColisaoProjPersInim(player);
					//dano colocado antes do desenho para dar a ilusão de maior tamanho da base
					base.LevarDano( horda.VerificarColisaoProjInimObj(base) );
					base.Draw();
					player.Draw();
					horda.Draw();
					al_flip_display();
					al_clear_to_color(al_map_rgb(0,0,0));					
				}
			}
		}
	}
	
	al_uninstall_mouse();
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_uninstall_system();
	return 0;
}
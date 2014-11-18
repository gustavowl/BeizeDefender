#include <iostream>
#include <allegro5/allegro.h>
#include <math.h>
#include "GameObject.h"
#include "ListaEncadeada/lista.h"
#include "Projetil.h"
#include "Base.h"
#include "Player.h"
#include "Inimigo.h"
//#include "Horda.h"

void *threadTiro(ALLEGRO_THREAD *thr, void *dados );
using namespace go;

GameObject arena(1024, 640); 
Player player(1024/2, 640/2);
Inimigo inimigo(2, 5);
Base base(380,200,620,440);

int main() {
  int i, X, Y, fps = 30;
  float v, qtd_ite = 0;
  bool done = false;
  
  
  //Horda horda(5, 1);
  
	//variaveis do allegro


	if( !al_init() )
		return -1;

	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_THREAD *thread = NULL;

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
	
	// Cria a thread e a dispara
    thread = al_create_thread(threadTiro, NULL);
    al_start_thread(thread);

	ALLEGRO_EVENT ev;

	while(!done)
	{
		if ( al_get_next_event(event_queue, &ev) ) {
		  //if (al_wait_for_event_until(event_queue, &ev, &timeout)) {

			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{	
				done = true;
			}
			else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
			{
				
			}
			else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
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
				//inimigo.Atirar(player);
				player.Mover(); //já move os projéteis do player
				//horda.Mover(player, base.GetRaio());
				inimigo.Distancia( player, base.GetRaio() ); //se tirar referência dá falha de segmentação
				//RESOLVER PROBLEMA NO CONSTRUTOR DE CÓPIA
				inimigo.Mover();
				//int i = 0;
				//dano colocado antes do desenho para dar a ilusão de maior tamanho da base
				base.LevarDano( inimigo.VerificarColisaoQuadrada(base) );
        
				//al_draw_rectangle(180, 160, 480, 320, al_map_rgb(255, 0, 255), 10);
				base.DrawBase();
				player.Draw();
				//DrawPlayer(player);
				//horda.LiberarInimigos();
				inimigo.Draw();
				//CollideProjetil(player, projeteis, 10, 2);
				al_flip_display();
				al_clear_to_color(al_map_rgb(0,0,0));
				//player.VerificarColisao(inimigo);
				player.LevarDano( inimigo.VerificarColisao(player) );
				inimigo.LevarDano( player.VerificarColisao(inimigo) );


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

void *threadTiro(ALLEGRO_THREAD *thr, void *dados )
{
    while(true)
    {
    	inimigo.Atirar(player);
        al_rest(1); // Atira a cada 1s
    }
    //return NULL;
}
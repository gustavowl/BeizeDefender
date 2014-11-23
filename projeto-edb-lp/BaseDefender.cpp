#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "GameOver.h"
#include "TelaInicial.h"
#include "GameManager.h"
#include "Instrucoes.h"

#define MAX_ALTURA 640
#define MAX_LARGURA 1024

#define GAME_STATE_MENU		 0
#define GAME_STATE_MAINGAME  1
#define GAME_STATE_INSTRUCOES 2
#define GAME_STATE_CREDITOS  3
#define GAME_STATE_GAMEOVER  4
#define GAME_STATE_VICTORY 5
#define GAME_STATE_FINISH    6

int main()
{
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_EVENT ev;

	int fps = 30, gameState = GAME_STATE_MENU;


	TelaInicial Menu;
	GameManager Jogo;
	Instrucoes Instrucao;
	GameOver Fim;


	if( !al_init() )
		return -1;
	//variaveis do allegro
	
	
	timer = al_create_timer(1.0 / fps);
	if (!timer)
		return -1;

	display = al_create_display( MAX_LARGURA, MAX_ALTURA );

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


	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);
	al_init_image_addon();

	while (gameState != GAME_STATE_FINISH && gameState != -1) 
	{
		if(gameState == GAME_STATE_MENU)
		{
			gameState = Menu.Executar(event_queue, ev, display);			
		}
		else if(gameState == GAME_STATE_MAINGAME)
		{
			gameState = Jogo.Executar(event_queue, ev, display, timer, MAX_LARGURA, MAX_ALTURA);
		}
		else if(gameState == GAME_STATE_INSTRUCOES)
		{
			/* Chamar Instruções */
			gameState = Instrucao.Executar(event_queue, ev, display);
		}
		else if(gameState == GAME_STATE_CREDITOS)

			/* Chamar Créditos */
			gameState = GAME_STATE_MENU;

		else if(gameState == GAME_STATE_GAMEOVER)
		{
			gameState = Fim.Executar(display);
		}
		else if(gameState == GAME_STATE_VICTORY)
		{
			gameState = GAME_STATE_CREDITOS;
		}
		else
		{
			gameState = GAME_STATE_FINISH;
		}
	}

	al_uninstall_mouse();
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_uninstall_system();

	return 0;
}
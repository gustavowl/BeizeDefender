#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <cstdlib>
#include <math.h>
#include <string>
#include "GameObject.h"
#include "ListaEncadeada/lista.h"
#include "Projetil.h"
#include "Base.h"
#include "Player.h"
#include "Inimigo.h"
#include "Horda.h"
#include "Waves.h"
#include "GameManager.h"
#include "Drop.h"

#define MAX_TIME 86400

using namespace go;

/*
#define GAME_STATE_MENU		 0
#define GAME_STATE_MAINGAME  1
#define GAME_STATE_GAMEOVER  2
#define GAME_STATE_FINISH    3
*/

#define MAX_HORDAS 15 // quantidade total das hordas
#define HORDA_BOSS 5 // quantidade de repetições para aparecer um boss
#define REGEM 15

GameManager::GameManager()
{}

void  GameManager::checkExpression (bool expression, std::string message)
{
	if (expression) {
		std::cout << message << std::endl;
		exit(1);
	}
}



int GameManager::Executar(ALLEGRO_EVENT_QUEUE * event_queue,  ALLEGRO_EVENT &ev, ALLEGRO_DISPLAY *display,
	ALLEGRO_TIMER *timer, int max_largura, int max_altura) {

	bool close = false;
	
    ALLEGRO_BITMAP *background1 = NULL;
    ALLEGRO_BITMAP *background2 = NULL;
    ALLEGRO_BITMAP *background3 = NULL;
    ALLEGRO_BITMAP *background4 = NULL;

	ALLEGRO_FONT *font = NULL;
	ALLEGRO_SAMPLE * tiro = NULL;
	ALLEGRO_AUDIO_STREAM * trilha = NULL;

    int tecla = 0;
    int hordaAtual = 1;
	int idHorda = 1;


	GameObject arena(max_largura, max_altura);
	
	Lista<Horda*> fila_horda(FILA);
	Lista<int> fila_tempo_espera(FILA);
	Lista<Drop*> lista_cafe(LISTASIMPLES);
	Drop cafe;


		

	Base base(380, 200, 620, 440, REGEM);
	Projetil proj_player(0, 0, 20, 1, 1, 2, 5);
	Player player(base.GetXAtual() , base.GetYAtual() , 50, 50, 15, 100, 10,REGEM, proj_player);
	Projetil proj_inimigo(0, 0, 20, 1, 1, 2, 1);

	/*Gera 3 "Fases" e 3 Boss*/
	/*Também aumenta a vida dos Inimigo e dos Boss*/
	for(int j = 1; j <= 3; ++j)
	{
		//gera horda para wave
		for (int i = 2; i <= 8; i+=2) {
			Horda* nova_horda = new Horda(idHorda, i, 2, 5*j, 10, 10, 30, 60, proj_inimigo);
			fila_horda.Insert( nova_horda );
			fila_tempo_espera.Insert( i * 15 ); //espera 1, 2 e 3 segundos
			idHorda++;
		}
		//gera boss
		Horda * boss;
		switch(j){
			case 1:
				boss = new Horda(idHorda, 1, 10, 50*j, 10, 10, 7, 15, proj_inimigo);
				break;
			case 2:
				boss = new Horda(idHorda, 1, 3, 50*j, 10, 15, 5, 15, proj_inimigo);
				break;
			case 3: 
				boss = new Horda(idHorda, 1, 10, 50*j, 4, 10, 7, 15, proj_inimigo);
				break;
		}
		fila_horda.Insert(boss);
		fila_tempo_espera.Insert(150);
		idHorda++;
	}
	
	/*  Múltiplas Waves */
	Waves wave = Waves( fila_horda, fila_tempo_espera);
   
	
	checkExpression(!al_install_audio(), "Problemas ao iniciar o plugin de audio. Abortar!");
	al_reserve_samples(5);
	checkExpression(!al_init_acodec_addon(), "Problemas ao iniciar o plugin adicional de audio. Abortar!");
	checkExpression(!al_install_keyboard(), "Problema ao iniciar o teclado");
	//checkExpression(!al_init_reserve_sample(1), "Problemas ao iniciar os canais de audio. Abortar!");

	trilha = al_load_audio_stream("die_motherfucker_die.wav", 5, 1024);
	checkExpression(!trilha, "Música não Carregada");

	tiro = al_load_sample("pistol.wav");

	al_attach_audio_stream_to_mixer(trilha, al_get_default_mixer());
	al_set_audio_stream_playmode(trilha, ALLEGRO_PLAYMODE_LOOP);

	//background = al_create_bitmap(1024,640);

	background1 = al_load_bitmap("base_concept1.png");
	background2 = al_load_bitmap("base_concept2.png");
	background3 = al_load_bitmap("base_concept3.png");
	background4 = al_load_bitmap("base_concept4.png");






	if(!al_load_bitmap("base_concept1.png")) {
		std::cout << "Image not loaded" << std::endl;
		return -1;
	}
	if(!al_load_bitmap("base_concept2.png")) {
		std::cout << "Image not loaded" << std::endl;
		return -1;
	}
	if(!al_load_bitmap("base_concept3.png")) {
		std::cout << "Image not loaded" << std::endl;
		return -1;
	}
	if(!al_load_bitmap("base_concept4.png")) {
		std::cout << "Image not loaded" << std::endl;
		return -1;
	}

	al_init_font_addon();

	if ( !al_init_ttf_addon() ) {
		std::cout << "Error: Font format not loaded" << std::endl;
		return -1;
	}

	/*if(!al_init_ttf_addon()) {
		std::cout << "Font not loaded" << std::endl;

		return -1;
	}*/

	
	font = al_load_font("PressStart2P.ttf", 15, 0);

	if(!font) 
	{
		return -1;
	}

	//al_init_primitives_addon();	

    al_register_event_source(event_queue, al_get_keyboard_event_source());

	srand(time(NULL));

	while( !close )
	{

		if ( al_get_next_event(event_queue, &ev) ) 
		{
		  //if (al_wait_for_event_until(event_queue, &ev, &timeout)) {

			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{	
				close = true;
			}

			
			//verifica se o jogo não acabou
			/*if (gamestate == GAME_STATE_MENU)
			{

				novo_jogo = al_load_bitmap("mnuNewGame.bmp");
				instrucoes = al_load_bitmap("mnuOptions.bmp");
				creditos = al_load_bitmap("mnuHighscoresM.bmp");
				sair = al_load_bitmap("mnuExit.bmp");

				al_draw_bitmap(novo_jogo, 384, 160, 0);
				al_draw_bitmap(instrucoes, 384, 240, 0);
				al_draw_bitmap(creditos, 384, 320, 0);
				al_draw_bitmap(sair, 448, 400, 0);

				if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
      			{
			        if(ev.mouse.button & 1)
			        {
			               /*Novo Jogo* /
			               if(ev.mouse.x >= 384 && ev.mouse.y >=160 && ev.mouse.y <= 206)
			               {
			               		gamestate = GAME_STATE_MAINGAME;
           						Inicializar();

			               }
			               /*Instruções* /
			               else if(ev.mouse.x >= 384 && ev.mouse.y >=240 && ev.mouse.y <= 291)
			                     std::cout << "eu faço algo" << std::endl;
			               /*Creditos* /
			               else if(ev.mouse.x >= 384 && ev.mouse.y >=320 && ev.mouse.y <= 369)
			                     std::cout << "eu faço algo" << std::endl;
			               /*Sair* /
			               else if(ev.mouse.x >= 448 && ev.mouse.y >=400 && ev.mouse.y <= 451)
			                     std::cout << "eu faço algo" << std::endl;
			        }
				}

				al_flip_display();
				al_clear_to_color( al_map_rgb(0,0,0));

			}*/


			if ( player.GetVida() > 0 && base.GetVida() > 0 && !wave.Destruida() ) 
  			{
				if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
						
						if(ev.mouse.button & 2) {
		          			player.AtualizarDestino(ev.mouse.x, ev.mouse.y);
						}

						else if(ev.mouse.button & 1)
						{
		          			player.Atirar(ev.mouse.x, ev.mouse.y); //oks
		          			al_play_sample(tiro, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

						}
				}


				
				else if (ev.type == ALLEGRO_EVENT_TIMER) 
				{
					player.Mover(); //já move os projéteis do player
					wave.Mover(player, base); //move projéteis da wave, msm se horda destruída (?)

					player.LevarDano( wave.VerificarColisaoProjInimObj(player) );
					//dano colocado antes do desenho para dar a ilusão de maior tamanho da base
					base.LevarDano( wave.VerificarColisaoProjInimObj(base) );

					base.Draw();

					if(base.GetVida() <= 100 && base.GetVida() > 75)
						al_draw_bitmap(background1, 0, 0, 0);
					else if(base.GetVida() <= 75 && base.GetVida() > 50)
						al_draw_bitmap(background2, 0, 0, 0);
					else if(base.GetVida() <= 50 && base.GetVida() > 25)
						al_draw_bitmap(background3, 0, 0, 0);
					else if(base.GetVida() <= 25 && base.GetVida() >= 0)
						al_draw_bitmap(background4, 0, 0, 0);


					if ( !wave.EsperandoProximaHorda() ) {
						//só atira caso horda não tenha sido destruída
						wave.Atirar(player, base);
						//verifica dano nos inimigos da horda
						wave.VerificarColisaoProjPersInim(player, lista_cafe);
					}
					else{
						if(wave.GetIdHorda() != hordaAtual){
							base.Regenerar();
							player.Regenerar();		
							hordaAtual++;
						}
					}


					player.Draw();
					cafe.Draw(lista_cafe, display);
					cafe.Pegar(player, lista_cafe);
					wave.Draw();
					al_draw_textf(font, al_map_rgb(0, 0, 200), 150, 10, ALLEGRO_ALIGN_RIGHT, "Vida: %d", player.GetVida());
					al_draw_textf(font, al_map_rgb(0, 0, 200), 300, 10, ALLEGRO_ALIGN_RIGHT, "Base: %d", base.GetVida());
					al_draw_textf(font, al_map_rgb(0, 0, 200), 480, 10, ALLEGRO_ALIGN_RIGHT, "Energia: %d", player.GetMunicaoAtual());
					al_draw_textf(font, al_map_rgb(0, 0, 200), 620, 10, ALLEGRO_ALIGN_RIGHT, "Horda: %d", wave.GetIdHorda());

					al_flip_display();
					al_clear_to_color(al_map_rgb(0,0,0));					
				}
				/* Entrada do Teclado */
				else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
				{
		
					switch(ev.keyboard.keycode) 
					{
						case ALLEGRO_KEY_Q:
							tecla = 1;
							break;
						case ALLEGRO_KEY_W:
							tecla = 2;
							break;
						default: 
							tecla = 0;
							break;
					}
					if (tecla != 0)
					{
						switch(tecla)
						{
							case 1:
							
								std::cout << "Tecla Q" << std::endl;
								player.ProxProjetil();

								tecla = 0;
								break;

							case 2:
							
								std::cout << "Tecla W" << std::endl;
								player.AntProjetil();

								tecla = 0;
								break;
						}
					}
					

				}
			}
			else
			{
				close = true;
			}
		}
	}

	al_destroy_bitmap(background1);
	al_destroy_bitmap(background2);
	al_destroy_bitmap(background3);
	al_destroy_bitmap(background4);

	al_destroy_audio_stream(trilha);
	al_shutdown_font_addon();
	al_destroy_font(font);
	al_shutdown_ttf_addon();

	//player venceu
	if(wave.Destruida()) {
		return 5;
	}
	//player perdeu
	else if (player.GetVida() <= 0 || base.GetVida() <= 0) {
		return 4;
	}
	//player fechou a tela
	else {
		return 6;
	}


	

	return 0;
}

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
#define MAX_ALTURA 640
#define MAX_LARGURA 1024
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

using namespace go;

int GameManager::Executar() {
    int fps = 30;
    int tecla = 0;
    bool done = false;
    int hordaAtual = 1;

	GameObject arena(MAX_LARGURA, MAX_ALTURA);
	Base base(380, 200, 620, 440, REGEM);
	Player player(base.GetXAtual() , base.GetYAtual() , 50, 50, 15, 100, 10, REGEM);
	Projetil proj_inimigo(0, 0, 20, 1, 1, 2, 1);
	Lista<Horda*> fila_horda(FILA);
	Lista<int> fila_tempo_espera(FILA);
	Lista<Drop*> lista_cafe(LISTASIMPLES);
	Drop cafe;

	/*Gera 15 "hordas" com 3 Boss*/
	int idHorda = 1;
	for(int j = 1; j <= 3; ++j){
		//gera horda para wave
		//for (int i = 3; i <= 12; i+=3) { // modo dificil
		for (int i = 2; i <= 8; i+=2) { // modo normal
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
	
	/*  Múltiplas hordas */
	Waves wave( fila_horda, fila_tempo_espera);

	if( !al_init() )
		return -1;

	//variaveis do allegro
	ALLEGRO_BITMAP *background = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_SAMPLE * tiro = NULL;
	ALLEGRO_AUDIO_STREAM * trilha = NULL;
	
	timer = al_create_timer(1.0 / fps);
	if (!timer)
		return -1;

	display = al_create_display( (int)arena.GetMaxX(), (int)arena.GetMaxY() );

	if (!display) {
		al_destroy_timer(timer);
		return -1;
	}

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
	font = al_load_font("WEST.TTF", 40, 0);

	if(!font){
		al_destroy_display(display);
		return -1;
	}

	//al_init_primitives_addon();	

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);

	ALLEGRO_EVENT ev;
	srand(time(NULL));
	while(!done){
		if ( al_get_next_event(event_queue, &ev) ) {
			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){	
				done = true;
			}
			/* Entrada do Teclado */
			else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
				switch(ev.keyboard.keycode){
					case ALLEGRO_KEY_Q:
						tecla = 1;
						break;
					case ALLEGRO_KEY_W:
						tecla = 2;
						break;
					case ALLEGRO_KEY_M:
						tecla = 3;
						break;
				}
				if (tecla){
					switch(tecla){
						case 1:
							player.ProxProjetil();
							tecla = 0;
							break;

						case 2:
							player.AntProjetil();
							tecla = 0;
							break;

						case 3:
							al_rest(MAX_TIME);
							tecla = 0;
							break;
					}
				}
			}
			else if(wave.Destruida()){
				// jogador ganhou
				std::cout<<"Ganhei"<<std::endl;
			}
			else if ( player.GetVida() == 0 || base.GetVida() == 0) {
				// jogador perdeu
				std::cout<<"Perdi"<<std::endl;
			}  
			//verifica se player && vida estão vivos
			else if ( player.GetVida() > 0 && base.GetVida() > 0 && !wave.Destruida() ) {
				if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
					if(ev.mouse.button & 2) {
	          			player.AtualizarDestino(ev.mouse.x, ev.mouse.y);
					}
					else if(ev.mouse.button & 1){
	          			player.Atirar(ev.mouse.x, ev.mouse.y); //oks
	          			al_play_sample(tiro, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
				}
				else if (ev.type == ALLEGRO_EVENT_TIMER) {
					player.Mover(); //já move os projéteis do player
					wave.Mover(player, base); //move projéteis da wave, msm se horda destruída (?)

					player.LevarDano( wave.VerificarColisaoProjInimObj(player) );
					//dano colocado antes do desenho para dar a ilusão de maior tamanho da base
					base.LevarDano( wave.VerificarColisaoProjInimObj(base) );

					base.Draw();
					al_draw_bitmap(background, 0, 0, 0);

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
					cafe.Draw(lista_cafe);
					cafe.Pegar(player, lista_cafe);
					wave.Draw();
					al_draw_textf(font, al_map_rgb(0, 0, 200), MAX_LARGURA, 0, ALLEGRO_ALIGN_RIGHT, "Vida: %d", player.GetVida());
					al_draw_textf(font, al_map_rgb(0, 0, 200), MAX_LARGURA, 45, ALLEGRO_ALIGN_RIGHT, "Base: %d", base.GetVida());
					al_draw_textf(font, al_map_rgb(0, 0, 200), MAX_LARGURA, 90, ALLEGRO_ALIGN_RIGHT, "Energia: %d", player.GetMunicaoAtual());
					al_draw_textf(font, al_map_rgb(0, 0, 200), MAX_LARGURA, 135, ALLEGRO_ALIGN_RIGHT, "Horda: %d", wave.GetIdHorda());
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
	al_destroy_audio_stream(trilha);
	al_uninstall_system();
	return 0;
}
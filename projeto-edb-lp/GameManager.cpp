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
#include "ListaEncadeada/FilaDupl.h"
#include "SpriteManip.h"
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
using namespace SpManip;

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
	/******************************
	*****INICIALIZA PLAYER*********
	*******************************/
	//bitmap para carregar imagens de player
	ALLEGRO_BITMAP *al_bmp_player = NULL;
	ALLEGRO_BITMAP *al_bmp_inim = NULL;
	ALLEGRO_BITMAP *al_bmp_proj = NULL;
	ALLEGRO_BITMAP *al_bmp_drop = NULL;
	//para iniciar sprite manip
	FilaDupl<ALLEGRO_BITMAP*> player_parado[8];
	FilaDupl<ALLEGRO_BITMAP*> player_andar[8];
	FilaDupl<ALLEGRO_BITMAP*> player_atirar[8];
	FilaDupl<ALLEGRO_BITMAP*> inim_parado[8];
	FilaDupl<ALLEGRO_BITMAP*> inim_andar[8];
	FilaDupl<ALLEGRO_BITMAP*> inim_atirar[8];
	FilaDupl<ALLEGRO_BITMAP*> proj_andar[8];
	FilaDupl<ALLEGRO_BITMAP*> drop_parado[8];
	//FilaDupl<ALLEGRO_BITMAP*> player_morrer[8];
	//CARREGA SPRITES
	//PARADO
	al_bmp_player = al_load_bitmap("Sprites/Beize/Parado/Cima/0.png");
	player_parado[CIMA].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Parado/Cima e Direita/0.png");
	player_parado[CIMADIR].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Parado/Direita/0.png");
	player_parado[DIREITA].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Parado/Baixo e Direita/0.png");
	player_parado[BAIXODIR].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Parado/Baixo/0.png");
	player_parado[BAIXO].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Parado/Baixo e Esquerda/0.png");
	player_parado[BAIXOESQ].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Parado/Esquerda/0.png");
	player_parado[ESQUERDA].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Parado/Cima e Esquerda/0.png");
	player_parado[CIMAESQ].Insert( al_bmp_player );

	/**************
	CARREGA SPRITES DO PLAYER SE MOVENDO
	**************/
	//ANDANDO
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima/0.png");
	player_andar[CIMA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima/1.png");
	player_andar[CIMA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima/2.png");
	player_andar[CIMA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima/3.png");
	player_andar[CIMA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima/4.png");
	player_andar[CIMA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima/5.png");
	player_andar[CIMA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima/6.png");
	player_andar[CIMA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima/7.png");
	player_andar[CIMA].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Direita/0.png");
	player_andar[CIMADIR].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Direita/1.png");
	player_andar[CIMADIR].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Direita/2.png");
	player_andar[CIMADIR].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Direita/3.png");
	player_andar[CIMADIR].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Direita/4.png");
	player_andar[CIMADIR].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Direita/5.png");
	player_andar[CIMADIR].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Direita/6.png");
	player_andar[CIMADIR].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Direita/7.png");
	player_andar[CIMADIR].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Direita/0.png");
	player_andar[DIREITA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Direita/1.png");
	player_andar[DIREITA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Direita/2.png");
	player_andar[DIREITA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Direita/3.png");
	player_andar[DIREITA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Direita/4.png");
	player_andar[DIREITA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Direita/5.png");
	player_andar[DIREITA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Direita/6.png");
	player_andar[DIREITA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Direita/7.png");
	player_andar[DIREITA].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Direita/0.png");
	player_andar[BAIXODIR].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Direita/1.png");
	player_andar[BAIXODIR].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Direita/2.png");
	player_andar[BAIXODIR].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Direita/3.png");
	player_andar[BAIXODIR].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Direita/4.png");
	player_andar[BAIXODIR].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Direita/5.png");
	player_andar[BAIXODIR].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Direita/6.png");
	player_andar[BAIXODIR].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Direita/7.png");
	player_andar[BAIXODIR].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo/0.png");
	player_andar[BAIXO].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo/1.png");
	player_andar[BAIXO].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo/2.png");
	player_andar[BAIXO].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo/3.png");
	player_andar[BAIXO].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo/4.png");
	player_andar[BAIXO].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo/5.png");
	player_andar[BAIXO].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo/6.png");
	player_andar[BAIXO].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo/7.png");
	player_andar[BAIXO].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Esquerda/0.png");
	player_andar[BAIXOESQ].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Esquerda/1.png");
	player_andar[BAIXOESQ].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Esquerda/2.png");
	player_andar[BAIXOESQ].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Esquerda/3.png");
	player_andar[BAIXOESQ].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Esquerda/4.png");
	player_andar[BAIXOESQ].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Esquerda/5.png");
	player_andar[BAIXOESQ].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Esquerda/6.png");
	player_andar[BAIXOESQ].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Baixo e Esquerda/7.png");
	player_andar[BAIXOESQ].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Esquerda/0.png");
	player_andar[ESQUERDA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Esquerda/1.png");
	player_andar[ESQUERDA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Esquerda/2.png");
	player_andar[ESQUERDA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Esquerda/3.png");
	player_andar[ESQUERDA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Esquerda/4.png");
	player_andar[ESQUERDA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Esquerda/5.png");
	player_andar[ESQUERDA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Esquerda/6.png");
	player_andar[ESQUERDA].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Esquerda/7.png");
	player_andar[ESQUERDA].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Esquerda/0.png");
	player_andar[CIMAESQ].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Esquerda/1.png");
	player_andar[CIMAESQ].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Esquerda/2.png");
	player_andar[CIMAESQ].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Esquerda/3.png");
	player_andar[CIMAESQ].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Esquerda/4.png");
	player_andar[CIMAESQ].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Esquerda/5.png");
	player_andar[CIMAESQ].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Esquerda/6.png");
	player_andar[CIMAESQ].Insert( al_bmp_player );
	al_bmp_player = al_load_bitmap("Sprites/Beize/Andar/Cima e Esquerda/7.png");
	player_andar[CIMAESQ].Insert( al_bmp_player );


	//ATIRANDO
	al_bmp_player = al_load_bitmap("Sprites/Beize/Atirar/Cima/0.png");
	player_atirar[CIMA].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Atirar/Cima e Direita/0.png");
	player_atirar[CIMADIR].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Atirar/Direita/0.png");
	player_atirar[DIREITA].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Atirar/Baixo e Direita/0.png");
	player_atirar[BAIXODIR].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Atirar/Baixo/0.png");
	player_atirar[BAIXO].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Atirar/Baixo e Esquerda/0.png");
	player_atirar[BAIXOESQ].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Atirar/Esquerda/0.png");
	player_atirar[ESQUERDA].Insert( al_bmp_player );

	al_bmp_player = al_load_bitmap("Sprites/Beize/Atirar/Cima e Esquerda/0.png");
	player_atirar[CIMAESQ].Insert( al_bmp_player );

	SpriteManip sp_player(player_parado, player_andar, player_atirar);

	/******************************
	*****INICIALIZA SPRITES PROJÉTEIS PLAYER*********
	*******************************/
	al_bmp_proj = al_load_bitmap("Sprites/ProjAmarelo1Menor.png");
	for (int i = 0; i < 8; i++) {
		proj_andar[i].Insert( al_bmp_proj );
	}

	SpriteManip sp_proj(proj_andar, proj_andar, proj_andar);

	Projetil proj_player(0, 0, 20, 1, 1, 2, 5, sp_proj);
	//LEMBRAR DE DESALOCAR MANUALMENTE SP_PLAYER E SEUS VALORES
	Player player(base.GetXAtual() , base.GetYAtual() , 50, 50, 12, 100, 10, REGEM, proj_player, sp_player,
		sp_proj, sp_proj, sp_proj);
	/******************************
	*****INICIALIZA SPRITES INIMIGO*********
	*******************************/
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Parado/Cima/0.png");
	inim_parado[CIMA].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Parado/Cima e Direita/0.png");
	inim_parado[CIMADIR].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Parado/Direita/0.png");
	inim_parado[DIREITA].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Parado/Baixo e Direita/0.png");
	inim_parado[BAIXODIR].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Parado/Baixo/0.png");
	inim_parado[BAIXO].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Parado/Baixo e Esquerda/0.png");
	inim_parado[BAIXOESQ].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Parado/Esquerda/0.png");
	inim_parado[ESQUERDA].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Parado/Cima e Esquerda/0.png");
	inim_parado[CIMAESQ].Insert( al_bmp_inim );
	/*************
	CARREGA SPRITES DOS INIMIGOS ANDANDO
	*************/
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima/0.png");
	inim_andar[CIMA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima/1.png");
	inim_andar[CIMA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima/2.png");
	inim_andar[CIMA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima/3.png");
	inim_andar[CIMA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima/4.png");
	inim_andar[CIMA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima/5.png");
	inim_andar[CIMA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima/6.png");
	inim_andar[CIMA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima/7.png");
	inim_andar[CIMA].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Direita/0.png");
	inim_andar[CIMADIR].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Direita/1.png");
	inim_andar[CIMADIR].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Direita/2.png");
	inim_andar[CIMADIR].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Direita/3.png");
	inim_andar[CIMADIR].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Direita/4.png");
	inim_andar[CIMADIR].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Direita/5.png");
	inim_andar[CIMADIR].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Direita/6.png");
	inim_andar[CIMADIR].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Direita/7.png");
	inim_andar[CIMADIR].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Direita/0.png");
	inim_andar[DIREITA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Direita/1.png");
	inim_andar[DIREITA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Direita/2.png");
	inim_andar[DIREITA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Direita/3.png");
	inim_andar[DIREITA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Direita/4.png");
	inim_andar[DIREITA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Direita/5.png");
	inim_andar[DIREITA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Direita/6.png");
	inim_andar[DIREITA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Direita/7.png");
	inim_andar[DIREITA].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Direita/0.png");
	inim_andar[BAIXODIR].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Direita/1.png");
	inim_andar[BAIXODIR].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Direita/2.png");
	inim_andar[BAIXODIR].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Direita/3.png");
	inim_andar[BAIXODIR].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Direita/4.png");
	inim_andar[BAIXODIR].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Direita/5.png");
	inim_andar[BAIXODIR].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Direita/6.png");
	inim_andar[BAIXODIR].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Direita/7.png");
	inim_andar[BAIXODIR].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo/0.png");
	inim_andar[BAIXO].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo/1.png");
	inim_andar[BAIXO].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo/2.png");
	inim_andar[BAIXO].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo/3.png");
	inim_andar[BAIXO].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo/4.png");
	inim_andar[BAIXO].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo/5.png");
	inim_andar[BAIXO].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo/6.png");
	inim_andar[BAIXO].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo/7.png");
	inim_andar[BAIXO].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Esquerda/0.png");
	inim_andar[BAIXOESQ].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Esquerda/1.png");
	inim_andar[BAIXOESQ].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Esquerda/2.png");
	inim_andar[BAIXOESQ].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Esquerda/3.png");
	inim_andar[BAIXOESQ].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Esquerda/4.png");
	inim_andar[BAIXOESQ].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Esquerda/5.png");
	inim_andar[BAIXOESQ].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Esquerda/6.png");
	inim_andar[BAIXOESQ].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Baixo e Esquerda/7.png");
	inim_andar[BAIXOESQ].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Esquerda/0.png");
	inim_andar[ESQUERDA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Esquerda/1.png");
	inim_andar[ESQUERDA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Esquerda/2.png");
	inim_andar[ESQUERDA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Esquerda/3.png");
	inim_andar[ESQUERDA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Esquerda/4.png");
	inim_andar[ESQUERDA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Esquerda/5.png");
	inim_andar[ESQUERDA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Esquerda/6.png");
	inim_andar[ESQUERDA].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Esquerda/7.png");
	inim_andar[ESQUERDA].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Esquerda/0.png");
	inim_andar[CIMAESQ].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Esquerda/1.png");
	inim_andar[CIMAESQ].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Esquerda/2.png");
	inim_andar[CIMAESQ].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Esquerda/3.png");
	inim_andar[CIMAESQ].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Esquerda/4.png");
	inim_andar[CIMAESQ].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Esquerda/5.png");
	inim_andar[CIMAESQ].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Esquerda/6.png");
	inim_andar[CIMAESQ].Insert( al_bmp_inim );
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Andar/Cima e Esquerda/7.png");
	inim_andar[CIMAESQ].Insert( al_bmp_inim );


	//ATIRANDO
	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Atirar/Cima/0.png");
	inim_atirar[CIMA].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Atirar/Cima e Direita/0.png");
	inim_atirar[CIMADIR].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Atirar/Direita/0.png");
	inim_atirar[DIREITA].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Atirar/Baixo e Direita/0.png");
	inim_atirar[BAIXODIR].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Atirar/Baixo/0.png");
	inim_atirar[BAIXO].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Atirar/Baixo e Esquerda/0.png");
	inim_atirar[BAIXOESQ].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Atirar/Esquerda/0.png");
	inim_atirar[ESQUERDA].Insert( al_bmp_inim );

	al_bmp_inim = al_load_bitmap("Sprites/Inimigo/Atirar/Cima e Esquerda/0.png");
	inim_atirar[CIMAESQ].Insert( al_bmp_inim );

	SpriteManip sp_inim(inim_parado, inim_andar, inim_atirar);

	/******************************
	*****INICIALIZA PROJÉTEIS INIMIGO*********
	*******************************/
	Projetil proj_inimigo(0, 0, 20, 1, 1, 2, 1, sp_proj);

	/*Gera 3 "Fases" e 3 Boss*/
	/*Também aumenta a vida dos Inimigo e dos Boss*/
	for(int j = 1; j <= 3; ++j)
	{
		//gera horda para wave
		for (int i = 2; i <= 8; i+=2) {
			Horda* nova_horda = new Horda(idHorda, i, 2, 5*j, 10, 10, 60, proj_inimigo, 5, sp_inim);
			fila_horda.Insert( nova_horda );
			fila_tempo_espera.Insert( i * 15 ); //espera 1, 2 e 3 segundos
			idHorda++;
		}
		//gera boss
		Horda * boss;
		switch(j){
			case 1:
				boss = new Horda(idHorda, 1, 3, 40*j, 10, 7, 15, proj_inimigo, 100, sp_inim);
				break;
			case 2:
				boss = new Horda(idHorda, 1, 3, 40*j, 10, 5, 15, proj_inimigo, 100, sp_inim);
				break;
			case 3: 
				boss = new Horda(idHorda, 1, 3, 40*j, 4, 7, 15, proj_inimigo, 100, sp_inim);
				break;
		}
		fila_horda.Insert(boss);
		fila_tempo_espera.Insert(150);
		idHorda++;
	}
	
	/*  Múltiplas Waves */
	Waves wave = Waves( fila_horda, fila_tempo_espera);
	/**********************************
	********SPRITES DROP***************
	**********************************/
	al_bmp_drop = al_load_bitmap("Sprites/Drop/coffee.png");
	drop_parado[CIMA].Insert( al_bmp_drop );

	al_bmp_drop = al_load_bitmap("Sprites/Drop/coffee.png");
	drop_parado[CIMADIR].Insert( al_bmp_drop );

	al_bmp_drop = al_load_bitmap("Sprites/Drop/coffee.png");
	drop_parado[DIREITA].Insert( al_bmp_drop );

	al_bmp_drop = al_load_bitmap("Sprites/Drop/coffee.png");
	drop_parado[BAIXODIR].Insert( al_bmp_drop );

	al_bmp_drop = al_load_bitmap("Sprites/Drop/coffee.png");
	drop_parado[BAIXO].Insert( al_bmp_drop );

	al_bmp_drop = al_load_bitmap("Sprites/Drop/coffee.png");
	drop_parado[BAIXOESQ].Insert( al_bmp_drop );

	al_bmp_drop = al_load_bitmap("Sprites/Drop/coffee.png");
	drop_parado[ESQUERDA].Insert( al_bmp_drop );

	al_bmp_drop = al_load_bitmap("Sprites/Drop/coffee.png");
	drop_parado[CIMAESQ].Insert( al_bmp_drop );

	SpriteManip sp_drop(drop_parado, drop_parado, drop_parado);
   
	
	checkExpression(!al_install_audio(), "Problemas ao iniciar o plugin de audio. Abortar!");
	al_reserve_samples(5);
	checkExpression(!al_init_acodec_addon(), "Problemas ao iniciar o plugin adicional de audio. Abortar!");
	checkExpression(!al_install_keyboard(), "Problema ao iniciar o teclado");
	//checkExpression(!al_init_reserve_sample(1), "Problemas ao iniciar os canais de audio. Abortar!");

	trilha = al_load_audio_stream("Music/die_motherfucker_die.wav", 5, 1024);
	checkExpression(!trilha, "Música não Carregada");

	tiro = al_load_sample("Music/pistol.wav");

	al_attach_audio_stream_to_mixer(trilha, al_get_default_mixer());
	al_set_audio_stream_playmode(trilha, ALLEGRO_PLAYMODE_LOOP);

	//background = al_create_bitmap(1024,640);

	background1 = al_load_bitmap("Sprites/Base/base_concept1.png");
	background2 = al_load_bitmap("Sprites/Base/base_concept2.png");
	background3 = al_load_bitmap("Sprites/Base/base_concept3.png");
	background4 = al_load_bitmap("Sprites/Base/base_concept4.png");


	if(!al_load_bitmap("Sprites/Base/base_concept1.png")) {
		std::cout << "Image not loaded" << std::endl;
		return -1;
	}
	if(!al_load_bitmap("Sprites/Base/base_concept2.png")) {
		std::cout << "Image not loaded" << std::endl;
		return -1;
	}
	if(!al_load_bitmap("Sprites/Base/base_concept3.png")) {
		std::cout << "Image not loaded" << std::endl;
		return -1;
	}
	if(!al_load_bitmap("Sprites/Base/base_concept4.png")) {
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

	
	font = al_load_font("Font/PressStart2P.ttf", 15, 0);

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

			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{	
				close = true;
			}


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
						wave.VerificarColisaoProjPersInim(player, lista_cafe, sp_drop);
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
					al_draw_textf(font, al_map_rgb(0, 0, 200), 480, 10, ALLEGRO_ALIGN_RIGHT, "Energia: %d", player.GetEnergiaAtual());
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
								player.ProxProjetil();
								tecla = 0;
								break;

							case 2:
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
	al_destroy_sample(tiro);
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

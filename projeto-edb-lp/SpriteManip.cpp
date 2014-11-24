#include "SpriteManip.h"
#include <allegro5/allegro_image.h>
#include <math.h>
#include <allegro5/allegro_primitives.h>

using namespace SpManip;

SpriteManip::SpriteManip() {
	DirecaoAlvo = BAIXO;
	AcaoAtual = PARADO;
	for ( int i = 0; i < QTD_DIRECOES; i++ ) {
		Parado[i] = FilaDupl<ALLEGRO_BITMAP*>(); //cria fulas duplas vazias
		Andar[i] = FilaDupl<ALLEGRO_BITMAP*>(); //cria fulas duplas vazias
		Atirar[i] = FilaDupl<ALLEGRO_BITMAP*>(); //cria fulas duplas vazias
		//Morrer[i] = FilaDupl<ALLEGRO_BITMAP*>(); //cria fulas duplas vazias
	}

}

SpriteManip::SpriteManip( FilaDupl<ALLEGRO_BITMAP*> parado[QTD_DIRECOES], 
	FilaDupl<ALLEGRO_BITMAP*> andar[QTD_DIRECOES], 
	FilaDupl<ALLEGRO_BITMAP*> atirar[QTD_DIRECOES]/*, 
	FilaDupl<ALLEGRO_BITMAP*> morrer[QTD_DIRECOES]*/ ) {

	DirecaoAlvo = BAIXO;
	AcaoAtual = PARADO;

	for ( int i = 0; i < QTD_DIRECOES; i++ ) {
		Parado[i] = parado[i]; //cria fulas duplas vazias
		Andar[i] = andar[i]; //cria fulas duplas vazias
		Atirar[i] = atirar[i]; //cria fulas duplas vazias
		//Morrer[i] = morrer[i]; //cria fulas duplas vazias
	}
}

SpriteManip::SpriteManip( int x_atual, int y_atual, int x_alvo, int y_alvo,
	FilaDupl<ALLEGRO_BITMAP*> parado[QTD_DIRECOES], 
	FilaDupl<ALLEGRO_BITMAP*> andar[QTD_DIRECOES], 
	FilaDupl<ALLEGRO_BITMAP*> atirar[QTD_DIRECOES]/*, 
	FilaDupl<ALLEGRO_BITMAP*> morrer[QTD_DIRECOES]*/, ACAO nova_acao ) {

	MudarAlvo(x_atual, y_atual, x_alvo, y_alvo);
	MudarAcaoAtual(nova_acao);

	for ( int i = 0; i < QTD_DIRECOES; i++ ) {
		Parado[i] = parado[i]; //cria fulas duplas vazias
		Andar[i] = andar[i]; //cria fulas duplas vazias
		Atirar[i] = atirar[i]; //cria fulas duplas vazias
		//Morrer[i] = morrer[i]; //cria fulas duplas vazias
	}
}

void SpriteManip::MudarAlvo( int x_atual, int y_atual, int x_alvo, int y_alvo ) {

	/*	SENTIDO HORÁRIO EM UM CÍRCULO
		0: 345º - 15º: DIREITA
		1: 15º - 75º: CIMADIR
		2: 75º - 105º: CIMA
		3: 105º - 165º: CIMAESQ
		4: 165º - 195º: ESQUERDA
		5: 195º - 255º: BAIXOESQ
		6: 255º - 285º: BAIXO
		7: 285º - 345º: BAIXODIR
	*/
	//seno de atual até alvo (cateto oposto / hipotenusa)
	double alvo_sen = (y_alvo - y_atual) / sqrt( pow( x_alvo - x_atual, 2 ) + pow( y_alvo - y_atual, 2 ) );
	//cosseno de atual até alvo (cateto adjacente / hipotenusa)
	double alvo_cos = (x_alvo - x_atual) / sqrt( pow( x_alvo - x_atual, 2 ) + pow( y_alvo - y_atual, 2 ) );

	DIRECAO nova_dir_alvo;

	//VERIFICANDO POSIÇÃO ALVO
	if ( alvo_cos > 0 && alvo_sen <= sin(15*PI/180) && alvo_sen >= sin(345*PI/180) ) {
		//DIREITA
		nova_dir_alvo = DIREITA;
	}
	else if ( alvo_cos >= cos(75*PI/180) && alvo_cos <= cos(15*PI/180) &&
		alvo_sen <= sin(75*PI/180) && alvo_sen >= sin(15*PI/180) ) {
		//CIMADIR
		nova_dir_alvo = BAIXODIR;
	}
	//sen >0: semi círculo de cima
	else if ( alvo_sen > 0 && alvo_cos <= cos(75*PI/180) && alvo_cos >= cos(105*PI/180) ) {
		//BAIXO
		nova_dir_alvo = BAIXO;
	}
	else if ( alvo_cos >= cos(165*PI/180) && alvo_cos <= cos(105*PI/180) &&
		alvo_sen >= sin(165*PI/180) && alvo_sen <= sin(105*PI/180) ) {
		//CIMAESQ
		nova_dir_alvo = BAIXOESQ;
	}
	else if ( alvo_cos < 0 && alvo_sen <= sin(165*PI/180) && alvo_sen >= sin(195*PI/180) ) {
		//ESQUERDA
		nova_dir_alvo = ESQUERDA;
	}
	else if ( alvo_cos >= cos(195*PI/180) && alvo_cos <= cos(255*PI/180) && 
		alvo_sen >= sin(255*PI/180) && alvo_sen <= sin(195*PI/180) ) {
		//BAIXOESQ
		nova_dir_alvo = CIMAESQ;
	}
	else if ( alvo_sen < 0 && alvo_cos >= cos(255*PI/180) && alvo_cos <= cos(285*PI/180) ) {
		//CIMA
		nova_dir_alvo = CIMA;
	}
	else {
		//BAIXODIR
		nova_dir_alvo = CIMADIR;
	}

	//se mudou de direção chama o primeiro sprite da ação atual
	if ( nova_dir_alvo != DirecaoAlvo ) {
		DirecaoAlvo = nova_dir_alvo;
		//desenhar primeira imagem
		ALLEGRO_BITMAP *temp;
		if ( AcaoAtual == PARADO ) {
			Parado[DirecaoAlvo].GetFirstElem(temp);
		}
		else if ( AcaoAtual == ANDAR ) {
			Andar[DirecaoAlvo].GetFirstElem(temp);
		}
		else { //AcaoAtual == ATIRAR
			Atirar[DirecaoAlvo].GetFirstElem(temp);
		}
		/*else { //AcaoAtual == MORRER
			Morrer[DirecaoAlvo].GetFirstElem(temp);
		}
		if (temp != NULL) {
			al_draw_bitmap(temp, 0, 0, 0);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}*/
	}
	//senão avança o sprite da ação atual
	/*else {
		AvancarSprite(x_atual, y_atual);
	}*/
	//fazer verificação para ver se mudou alguma direção, se mudou a direção, chama novo sprite baseado na ação
}

void SpriteManip::MudarAcaoAtual( ACAO nova_acao ) {
	if ( nova_acao != AcaoAtual ) {
		AcaoAtual = nova_acao;
	}
}

//avançar sprite não muda automaticamente quando a ação muda
//avança sprite levando em conta alvo e destino, pode mudar o sentido de execução dependendo deles também
void SpriteManip::AvancarSprite(unsigned int x, unsigned int y) {
	ALLEGRO_BITMAP *teste;
	if ( AcaoAtual == PARADO ) {
		Parado[DirecaoAlvo].GetPrevElem(teste);
		if (teste != NULL) {
			al_draw_bitmap(teste, x - al_get_bitmap_width(teste) / 2,
				y - al_get_bitmap_height(teste) / 2, 0);
			//al_flip_display();
			//al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	else if ( AcaoAtual == ANDAR ) {
		Andar[DirecaoAlvo].GetPrevElem(teste);
		if (teste != NULL) {
			al_draw_bitmap(teste, x - al_get_bitmap_width(teste) / 2,
				y - al_get_bitmap_height(teste) / 2, 0);
			//al_flip_display();
			//al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	else { //AcaoAtual == ATIRAR
		Atirar[DirecaoAlvo].GetPrevElem(teste);
		if (teste != NULL) {
			al_draw_bitmap(teste, x - al_get_bitmap_width(teste) / 2,
				y - al_get_bitmap_height(teste) / 2, 0);
			//al_flip_display();
			//al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	/*else { //AcaoAtual == MORRER
		Morrer[DirecaoAlvo].GetPrevElem(teste);
		if (teste != NULL) {
			al_draw_bitmap(teste, 0, 0, 0);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}*/
}

SpriteManip::~SpriteManip() {

}

void SpriteManip::operator=(const SpriteManip &spm) {
	DirecaoAlvo = spm.DirecaoAlvo;
	AcaoAtual = spm.AcaoAtual;

	for ( int i = 0; i < QTD_DIRECOES; i++ ) {
		Parado[i] = spm.Parado[i];
		Andar[i] = spm.Andar[i];
		Atirar[i] = spm.Atirar[i];
		//Morrer[i] = morrer[i]; //cria fulas duplas vazias
	}
}
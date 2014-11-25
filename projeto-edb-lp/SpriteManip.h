#ifndef _SPRITEMANIP_H_
#define _SPRITEMANIP_H_
	#include <allegro5/allegro.h>
	#include "ListaEncadeada/FilaDupl.h"
	//#include <cstddef>

namespace SpManip {
	#define QTD_DIRECOES 8
	#define PI 3.1415926535897932
	#define INTERVALO_ENTRE_SPRITES 2
	//CIMA = 0, CIMADIR = 1....
	enum DIRECAO {CIMA = 0, CIMADIR, DIREITA, BAIXODIR,
		BAIXO, BAIXOESQ, ESQUERDA, CIMAESQ};

	enum ACAO { PARADO = 0, ANDAR, ATIRAR/*, MORRER */};

	class SpriteManip {
		//vetor com ponteiros de imagens nas 8 direções
	private:
		int TempoProxSprite;
		DIRECAO DirecaoAlvo; //aponta para onde está mirando / olhando
		ACAO AcaoAtual = PARADO;

		//sprites que serão movidos quando objeto estiver parado
		FilaDupl<ALLEGRO_BITMAP*> Parado[QTD_DIRECOES];
		//sprites que serão movidos quando objeto estiver andando
		FilaDupl<ALLEGRO_BITMAP*> Andar[QTD_DIRECOES];
		//sprites que serão movidos quando objeto estiver atirando
		FilaDupl<ALLEGRO_BITMAP*> Atirar[QTD_DIRECOES];
		//sprites que serão movidos quando objeto estiver morrendo
		//FilaDupl<ALLEGRO_BITMAP*> Morrer[QTD_DIRECOES];
	public:
		//COSTRUTORES
		//Construtor vazio
		SpriteManip();
		//construtores não recebem referência para não deletar ponteiros de onde foram chamados
		//NECESSÁRIO DESTRUIR PONTEIROS DE ALLEGRO_BITMAP EM GM
		//Construtor com Direções de destino e de alvo padrões
		SpriteManip( FilaDupl<ALLEGRO_BITMAP*> parado[QTD_DIRECOES], 
			FilaDupl<ALLEGRO_BITMAP*> andar[QTD_DIRECOES], 
			FilaDupl<ALLEGRO_BITMAP*> atirar[QTD_DIRECOES]/*, 
			FilaDupl<ALLEGRO_BITMAP*> morrer[QTD_DIRECOES]*/ );
		//Construtor com Direções de destino e de alvo enviados
		SpriteManip( int x_atual, int y_atual, int x_alvo, int y_alvo,
			FilaDupl<ALLEGRO_BITMAP*> parado[QTD_DIRECOES], 
			FilaDupl<ALLEGRO_BITMAP*> andar[QTD_DIRECOES], 
			FilaDupl<ALLEGRO_BITMAP*> atirar[QTD_DIRECOES]/*, 
			FilaDupl<ALLEGRO_BITMAP*> morrer[QTD_DIRECOES]*/, ACAO nova_acao );
		//DESTRUTOR
		//destrutor não desaloca ponteiros de imagens
		~SpriteManip();
		//muda direção de destino
		void MudarAlvo( int x_atual, int y_atual, int x_alvo, int y_alvo );
		//recalcular direcao de destino e alvo

		//chamar mudar ação antes de mudar destino para mudar o sprite instantaneamente
		void MudarAcaoAtual( ACAO nova_acao );

		int GetTempoProxSprite();
		void SetTempoProxSprite(int novoTempo);

		//ao chamar MudarDestinoOuAlvo(), não precisa chamar AvancarSprite()
		//avança sprite levando em conta alvo e destino, pode mudar o sentido de execução dependendo deles também
		bool AvancarSprite(unsigned int x, unsigned int y, unsigned int &larg, unsigned int &alt);
		bool RetrocederSprite(unsigned int x, unsigned int y, unsigned int &larg, unsigned int &alt);
		//sobrecarga de operador
		void operator=(const SpriteManip &spm);

		void Destruir();

	};

}
#endif
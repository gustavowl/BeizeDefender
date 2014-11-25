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

	/**
	* \class SpriteManip
	*
	* \brief Classe manipuladora de sprites. Há 3 tipos de ações possíveis: parado, andando e atirando
	*/

	class SpriteManip {

	private:
		int TempoProxSprite; /**< Tempo (em frames) para desenhar o próximo sprite desejado */
		DIRECAO DirecaoAlvo; /**< Armazena a direção a qual o objeto está apontando no momento*/
		ACAO AcaoAtual = PARADO; /**< Armazena Ação que o objeto está executando no momento */

		/**
		* Array de filas duplamente encadeada que contém os sprites, em cada uma das 8 direções
		* do objeto em questão quando está parado
		*/
		FilaDupl<ALLEGRO_BITMAP*> Parado[QTD_DIRECOES];
		/**
		* Array de Filas duplamente encadeada que contém os sprites, em cada uma das 8 direções
		* do objeto em questão quando está andando
		*/
		FilaDupl<ALLEGRO_BITMAP*> Andar[QTD_DIRECOES];
		/**
		* Array de filas duplamente encadeada que contém os sprites, em cada uma das 8 direções
		* do objeto em questão quando está atirando
		*/
		FilaDupl<ALLEGRO_BITMAP*> Atirar[QTD_DIRECOES];

	public:

		/**
		* Construtor padrão
		* aponta o objeto para baixo, com ação parado e inicia as filas de sprites como vazias
		*/
		SpriteManip();

		/**
		* Construtor
		* aponta o objeto para baixo, com ação parado e inicia filas com os valores enviados por parâmetro
		* @param parado[QTD_DIRECOES], array de filas com os sprites da animação do objeto parado em cada uma
		* das 8 direções
		* @param parado[QTD_DIRECOES], array de filas com os sprites da animação do objeto andando em cada uma
		* das 8 direções
		* @param parado[QTD_DIRECOES], array de filas com os sprites da animação do objeto atirando em cada uma
		* das 8 direções
		*/
		SpriteManip( FilaDupl<ALLEGRO_BITMAP*> parado[QTD_DIRECOES], 
			FilaDupl<ALLEGRO_BITMAP*> andar[QTD_DIRECOES], 
			FilaDupl<ALLEGRO_BITMAP*> atirar[QTD_DIRECOES] );

		/**
		* Construtor
		* calcula a direção para qual o objeto apontará baseado, nos valores mandados por parâmetro
		* e inicia filas com os valores também enviados. Ação recebida por parãmetro será Ação Atual
		* @param x_atual coordenada x da posição atual do objeto
		* @param y_atual coordenada y da posição atual do objeto
		* @param x_alvo coordenada x da posição para qual objeto se direciona
		* @param y_alvo coordenada y da posição para qual objeto se direciona
		* @param parado[QTD_DIRECOES], array de filas com os sprites da animação do objeto parado em cada uma
		* das 8 direções
		* @param parado[QTD_DIRECOES], array de filas com os sprites da animação do objeto andando em cada uma
		* das 8 direções
		* @param parado[QTD_DIRECOES], array de filas com os sprites da animação do objeto atirando em cada uma
		* das 8 direções
		* @param nova_acao recebe valor para AcaoAtual do objeto
		*/
		SpriteManip( int x_atual, int y_atual, int x_alvo, int y_alvo,
			FilaDupl<ALLEGRO_BITMAP*> parado[QTD_DIRECOES], 
			FilaDupl<ALLEGRO_BITMAP*> andar[QTD_DIRECOES], 
			FilaDupl<ALLEGRO_BITMAP*> atirar[QTD_DIRECOES], 
			ACAO nova_acao );

		/**
		* DESTRUTOR
		*/
		~SpriteManip();

		/**
		* Utilizado quando o objeto mudar de alvo, calcula a nova direção pra onde apontará
		* @param x_atual coordenada x da posição atual do objeto
		* @param y_atual coordenada y da posição atual do objeto
		* @param x_alvo coordenada x da posição para qual objeto se direciona
		* @param y_alvo coordenada y da posição para qual objeto se direciona
		*/
		void MudarAlvo( int x_atual, int y_atual, int x_alvo, int y_alvo );

		/**
		* Muda a ação atual do objeto
		* @param nova_acao recebe valor que será atribuido à AcaoAtual
		*/
		void MudarAcaoAtual( ACAO nova_acao );

		/**
		* \return Retorna o tempo (frames) restantes para próxima mudança de sprites
		*/
		int GetTempoProxSprite();
		/**
		* Retorna as dimensões (largura e altura) do sprite atual. Se chamado assim que criado
		* mostra as dimensões do primeiro sprite a ser desenhado, caso seja chamado em momentos posteriores
		* mostra as dimensões do último sprite desenhado (AcaoAtual[DirecaoAtual].GetLastGet())
		* \return Retorna se os valores alterados por referência são válidos 
		* @param &larg retorna, por referência, a largura do sprite atual
		* @param &alt retorna, por referência, a altura do sprite atual
		*/
		bool GetLastGetSpriteDimensao(unsigned int &larg, unsigned int &alt);

		/**
		* Altera o tempo (frames) até mudança do próximo sprite, não possui valor máximo
		* @param novoTempo novo tempo (frames) que será aguardado até que possa mudar de sprites novamente
		*/
		void SetTempoProxSprite(int novoTempo);


		/**
		* Diminui o tempo de espera para o próximo sprite, se for igual a 0, desenho o próximo sprite na fila,
		* caso contrário, redesenha o atual.
		* \return Retorna se os valores alterados por referência são válidos 
		* @param x posição x atual
		* @param y posição y atual
		* @param &larg retorna, por referência, a largura do sprite atual
		* @param &larg retorna, por referência, a altura do sprite atual
		*/
		bool AvancarSprite(unsigned int x, unsigned int y, unsigned int &larg, unsigned int &alt);

		/**
		* Diminui o tempo de espera para o próximo sprite, se for igual a 0, desenho o sprite anterior na fila,
		* caso contrário, redesenha o atual.
		* \return Retorna se os valores alterados por referência são válidos 
		* @param x posição x atual
		* @param y posição y atual
		* @param &larg retorna, por referência, a largura do sprite atual
		* @param &larg retorna, por referência, a altura do sprite atual
		*/
		bool RetrocederSprite(unsigned int x, unsigned int y, unsigned int &larg, unsigned int &alt);

		/**
		* Realiza cópia profunda do objeto enviado por parâmetro
		* @param &spm conjunto de sprites a serem copiados
		*/
		void operator=(const SpriteManip &spm);

		/**
		* Remove todos os elementos das filas de sprite e chama al_destroy_bitmap para cada instância de imagem.
		* É necessário que cada animação tenham imagens derivadas de fontes distintas
		*/
		void Destruir();

	};

}
#endif
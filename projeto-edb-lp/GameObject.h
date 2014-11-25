#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "SpriteManip.h"
#include "ListaEncadeada/lista.h"
/**
Enum que amazena os 3 tipos de movimentos: estático, linear ou smoothstep
*/

enum WalkType { STATIC, LINEAR, SMOOTH };
namespace go {

/**
* \class GameObject
*
* \brief Classe genérica de objeto de jogo. Contém os atributos mais básicos
*
* 
*
*/

class GameObject {
	protected:
		static unsigned int MaxX; /**< Armazena largura da arena*/
		static unsigned int MaxY; /**< Armazena altura da arena*/
		unsigned int FrameAtual = 0; /**< Armazena frame atual do movimento*/
		unsigned int TotalFrames = 0; /**< Armazena quantidade de frames necessárias pelo movimento 
		até atingir o destino. FrameAtual/TotalFrames resulta no valor de "t" utilizado na equação vetorial da reta*/

		unsigned int XOrigem; /**< Armeza posição X em que movimento foi iniciado. Necessário para calcular interpolação linear*/
		unsigned int YOrigem; /**< Armeza posição Y em que movimento foi iniciado. Necessário para calcular interpolação linear*/

		unsigned int XAtual; /**< Armeza posição X atual. É utilizado para detectar colisão*/
		unsigned int YAtual; /**< Armeza posição Y atual. É utilizado para detectar colisão*/

		unsigned int XDestino; /**< Armeza posição X em que movimento será finalizado. Necessário para calcular interpolação linear*/
		unsigned int YDestino; /**< Armeza posição Y em que movimento será finalizado. Necessário para calcular interpolação linear*/

		unsigned int Raio; /**< Raio do objeto. É utilizado para detectar colisões*/
		unsigned int Largura; /**< Largura do sprite atual. É utilizado para detectar colisões */
		unsigned int Altura; /**< Largura do sprite atual. É utilizado para detectar colisões */
		unsigned int Velocidade; /**<  Velocidade do objeto. A quantidade Total de frames da interpolação será calculada pela
		* distância entre o ponto de origem ao ponto de destino dividido pela Velocidade */

		WalkType TipoMovimento; /**< Armazena o tipo de movimento do objeto. Os 3 tipos de movimentos estão presentes no enum*/
		SpManip::SpriteManip Sprites; /**< Armazena ponteiros para as imagens (sprites) do objeto*/

	public:
		/**
		* Atualiza a posição atual de acordo com a interpolação linear.
		* Para calcular a posição leva em conta a velocidade.
		* Essa função deve ser chamada a cada frame.
		*/
		virtual void Mover();

		/**
		* Atualiza os atributos XOrigem, YOrigem, XDestino e YDestino, FrameAtual e recalcula TotalFrames.
		* @param DestinoX coordenada X de destino
		* @param DestinoY coordenada Y de destino
		*/
		virtual void AtualizarDestino(unsigned int DestinoX, unsigned int DestinoY);

		/**
		* Desenha objeto na posição atual, leva em conta imagens em SpManip::SpriteManip Sprites.
		* Avança sprite e o tempo de espera para desenhar próximo sprite
		*/
		virtual void Draw();

		/**
		* Retorna largura da arena, é utilizado para verificação de valores válidos em classes filhas.
		*/
		unsigned int GetMaxX() const;

		/**
		* Retorna altura da arena, é utilizado para verificação de valores válidos em classes filhas.
		*/
		unsigned int GetMaxY() const;

		/**
		* Retorna coordenadas X e Y da posição atual. Utilizado para calcular colisão
		* @param &x receberá a coordenada X da posição atual por referência
		* @param &y receberá a coordenada y da posição atual por referência
		*/
		void GetPosicaoAtual(unsigned int &x, unsigned int &y) const;

		/**
		* Retorna coordenada X posição atual. Utilizado em construtores das classes filhas
		*/
		unsigned int GetXAtual() const;

		/**
		* Retorna coordenada Y posição atual. Utilizado em construtores das classes filhas
		*/
		unsigned int GetYAtual() const;

		/**
		* Retorna Frame atual. Utilizado em construtores das classes filhas
		*/
		unsigned int GetFrameAtual() const;

		/**
		* Retorna Total de frames. Utilizado em construtores das classes filhas
		*/
		unsigned int GetTotalFrames() const;

		/**
		* Retorna coordenada X de origem. Utilizado em construtores das classes filhas
		*/
		unsigned int GetXOrigem() const;

		/**
		* Retorna coordenada Y de origem. Utilizado em construtores das classes filhas
		*/
		unsigned int GetYOrigem() const;

		/**
		* Retorna coordenada X de Destino. Utilizado em construtores das classes filhas
		*/
		unsigned int GetXDestino() const;

		/**
		* Retorna coordenada Y de Destino. Utilizado em construtores das classes filhas
		*/
		unsigned int GetYDestino() const;

		/**
		* Retorna raio de colisão. Utilizado em construtores das classes filhas
		*/
		unsigned int GetRaio() const;

		/**
		* Retorna largura do objeto. Utilizado em construtores das classes filhas
		*/
		unsigned int GetLargura() const;

		/**
		* Retorna altura do objeto. Utilizado em construtores das classes filhas
		*/
		unsigned int GetAltura() const;


		/**
		* Retorna velocidade do objeto. Utilizado em construtores das classes filhas
		*/
		unsigned int GetVelocidade() const;

		/**
		* Retorna tipo do movimento do objeto. Utilizado em construtores das classes filhas
		*/
		WalkType GetTipoMovimento() const;

		/**
		* \return Retorna instância de objeto manipulador de sprites. Utilizado em construtores de classes filhas
		*/
		SpManip::SpriteManip GetSprites() const;

		/**
		* Construtor padrão. Cria "objeto vazio".
		*/
		GameObject();

		/**
		* Construtor que deve ser chamado antes da construção de qualquer outro GameObject.
		* Inicializa as dimensões da arena. Só permite a inicialização, sem possibilidade de alteração.
		* @param MaximoX largura da arena
		* @param MaximoY altura da arena
		*/
		GameObject(unsigned int MaximoX, unsigned int MaximoY);

		/**
		* Construtor utilizado pelos inimigos.
		* Gera posição inicial aleatória nas bordas da arena e cria um objeto com os parâmetros enviados.
		* A posição será gerada de maneira que o novo inimigo não sobreponha nenhum dos objetos criados
		* anteriormente (enviados por parâmetro)
		* @param Velocidade velocidade do objeto
		* @param Raio raio utilizado para detecção de colisão
		* @param TipoMov tipo de movimento que será feito pelo objeto
		* @param sprites Recebe instância de classe que controlará sprites do objeto
		* @param &list_inim recebe por referência lista de inimigos já criados. Possibilita que o novo inimigo
		* não sobreponha nenhum deles ao ser criado
		*/
		GameObject(unsigned int Velocidade, unsigned int Raio, WalkType TipoMov, SpManip::SpriteManip sprites,
			Lista<GameObject*> &list_inim);

		/**
		* Construtor utilizado pelo player.
		* @param PositionX coordenada X de origem do objeto
		* @param PositionY coordenada X de origem do objeto
		* @param Velocidade velocidade do objeto
		* @param Raio raio utilizado para detecção de colisão
		* @param TipoMov tipo de movimento que será feito pelo objeto
		* @param sprites Recebe instância de classe que controlará sprites do objeto
		*/
		GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, unsigned int Raio, WalkType TipoMov,
			SpManip::SpriteManip sprites);

		/**
		* Construtor utilizado pelo projétil.
		* @param PositionX coordenada X de origem do objeto
		* @param PositionY coordenada X de origem do objeto
		* @param Velocidade velocidade do objeto
		* @param DestinoX coordenada X do destino do objeto
		* @param DestinoY coordenada Y do destino do objeto
		* @param Raio raio utilizado para detecção de colisão
		* @param TipoMov tipo de movimento que será feito pelo objeto
		* @param sprites Recebe instância de classe que controlará sprites do objeto
		*/
		GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, 
			unsigned int DestinoX, unsigned int DestinoY, unsigned int Raio, WalkType TipoMov,
			SpManip::SpriteManip sprites);

		/**
		* Destrutor
		*/
		~GameObject();
};

}

#endif
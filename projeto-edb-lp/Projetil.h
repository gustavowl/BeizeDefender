#ifndef _PROJETIL_H_
#define _PROJETIL_H_

#include "GameObject.h"
#include "SpriteManip.h"

/**
* \class Projetil
*
* \brief Classe que gerencia os projéteis lançados pelos personagens
*/

class Projetil : public go::GameObject {
	//velocidade padrão da bala: 30
	//raio padrão da bala: 2
	//walktype: linear
	private:
		unsigned int Dano; /**< Armazena dano que será causado pelo projétil*/
		bool Destruido; /**< Armazena se projétil foi destruído para que possa ser removido da lista que o contém*/

		/**
		* Calcula coordenada de destino do projétil, ou seja, a coordena na qual ele sairá da arena, retornando
		* essa posição por referência.
		* @param OrigemX coordenada X onde o objeto foi criado
		* @param OrigemY coordenada Y onde o objeto foi criado
		* @param &DestinoX recebe coordena X do primeiro destino e retorna coordenada X do destino final
		* @param &DestinoY recebe coordena Y do primeiro destino e retorna coordenada Y do destino final
		*/
		void CalcularCoordenadasFinais(unsigned int OrigemX, unsigned int OrigemY, unsigned int &DestinoX,
			unsigned int &DestinoY);

	public:
		/**
		* Construtor
		* Inicializa "projétil vazio", já destruído
		*/
		Projetil();
		/**
		* Construtor de projétil padrão
		* inicializa bala com velocidade e tamanho padrão
		* @param PositionX coordenada X de origem do projétil
		* @param PositionY coordenada Y de origem do projétil
		* @param DestinoX coordenada X de destino do projétil
		* @param DestinoY coordenaada Y de destino do projétil
		*/
		Projetil(unsigned int PositionX, unsigned int PositionY, unsigned int DestinoX, unsigned int DestinoY);

		/**
		* Construtor "total" de projétil
		* Inicializa projétil personalizado com os valores enviados por parâmetro
		* @param PositionX coordenada X de origem do projétil
		* @param PositionY coordenada Y de origem do projétil
		* @param Velocidade velocidade do projétil
		* @param DestinoX coordenada X de destino do projétil
		* @param DestinoY coordenaada Y de destino do projétil
		* @param Raio raio utilizado para detecção de colisão
		* @param Dano dano que será causado pelo projétil
		*/
		Projetil(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, unsigned int DestinoX,
			unsigned int DestinoY, unsigned int Raio, unsigned int Dano, SpManip::SpriteManip sp_proj);
		/**
		* Construtor de cópia
		* Realiza cópia profunda do projétil enviada por referência
		* @param &projetil projétil enviado por referência, de onde serão copiados os valores
		*/
		Projetil(const Projetil &projetil);

		/**
		* Sobrecarga de operador =
		* Realiza cópia profunda do GameObject enviado por referência
		* @param &GameObj GameObject enviado por referência, de onde serão copiados os valores
		*/
		void operator=(const GameObject &GameObj);
		/**
		* Sobrecarga de operador =
		* Realiza cópia profunda do projétil enviada por referência
		* @param &projetil projétil enviado por referência, de onde serão copiados os valores
		*/
		void operator=(const Projetil &proj);
		/**
		* Atualiza posição do projétil e altera o valor de Destruido para verdadeiro caso tenha
		* atingido a borda da arena
		*/
		void Mover();
		/**
		* Altera o valor de Destruido para verdadeiro
		*/
		void Destruir();
		/**
		* Desenha o projétil na arena de acordo com a posição atual
		*/
		void Draw();
		/**
		* Retorna se o projétil atual foi destruído
		* \return Retorna se o projétil atual foi destruído
		*/
		bool GetDesruido();
		/**
		* Retorna dano causado pelo projétil (atributo dano)
		* \return Retorna dano causado pelo projétil (atributo dano)
		*/
		unsigned int GetDano();
		/**
		* Identifica colisão do projétil com o obj circular enviado por parâmetro. Geralmente do tipo Personagem.
		* Retorna dano causado pelo projétil ao obj e destrói (altera valor do atributo "Destruido") projétil atual.
		* Função exterior tem q tirar vida do obj e remover projétil da memória.
		* \return Retorna dano causado pelo projétil no obj ( se 0, não colidiu, caso contrário, colidiu e causou dano)
		* @param obj GameObject com o qual será verificada a colisão do projétil atual
		*/
		int VerificarColisao(const GameObject obj);
		/**
		* Identifica colisão do projétil com o obj quadrado enviado por parâmetro. Geralmente do tipo base.
		* Retorna dano causado pelo projétil ao obj e destrói (altera valor do atributo "Destruido") projétil atual.
		* Função exterior tem q tirar vida do obj e remover projétil da memória.
		* \return Retorna dano causado pelo projétil no obj ( se 0, não colidiu, caso contrário, colidiu e causou dano)
		* @param obj GameObject com o qual será verificada a colisão do projétil atual
		*/
		int VerificarColisaoQuadrada(const GameObject obj);

};

#endif
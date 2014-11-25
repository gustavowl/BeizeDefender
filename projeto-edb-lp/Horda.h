#ifndef _HORDA_H_
#define _HORDA_H_

#include "Inimigo.h"
#include "Personagem.h"
#include "GameObject.h"
#include "Projetil.h"
#include "Drop.h"
#include "Player.h"
#include "SpriteManip.h"

/**
* \class Horda
*
* \brief Classe responsável por gerar as hordas/grupos de inimigos, 
* além de ser responsável por verificar os processos de colisões
*  
* 
*
*/

class Horda {

	private:
		int id; /**< Identifica o número da horda atual */ 
		Lista<Inimigo*> listaInimigos; /**< Lista simplesmente encadeada de inimigos */ 


	public:

		/**
		* Construtor padrão
		* Cria uma horda vazia
		*/
		Horda(); 

		/**
		* Construtor que gera umaa horda com uma quantidade específica de inimigos e com atributos "padrão"
		* @param quantidade quantia de inimigos a serem criados
		*/
		Horda(int quantidade);

		/**
		* Construtor que gera uma horda de inimigos com atributos específicos
		*
		* @param idHorda número da horda atual
		* @param quantidade número de inimigos
		* @param velocidade velocidade dos inimigos
		* @param vida pontos de vida dos inimigos
		* @param raio tamanho do inimigo
		* @param intervalo_tiro intervalo de tempo entre os disparos
		* @param primeiro_tiro intervalo de tempo para o primeiro disparo
		* @param projetil_base projetil a ser disparado pelo inimigo
		* @param danoFisico  dano físico de cada disparo
		* @param sp_inim Recebe instância de classe que controlará sprites do objeto (inimigo)
		* @param &list_inim recebe por referência lista de inimigos já criados. Possibilita que o novo inimigo
		*/
		Horda(int idHorda, int quantidade, int velocidade, int vida, int raio, int intervalo_tiro,
			int primeiro_tiro, Projetil projetil_base, int danoFisico, SpManip::SpriteManip sp_inim);

		/**
		* Destrutor padrão
		* Remove "Inimigo" da lista, além de deletar a instância de "Inimigo" dinamicamente alocada
		*
		*/
		~Horda();

		/**
		* Desenha os Inimigos da horda
		*/
		void Draw();

		/**
		* Dispara os projeteis dos inimigos em direção do "player" ou da "base", dependendo de quem estiver mais perto
		*
		* @param p personagem
		* @param base base do jogo
		*/
		void Atirar(Personagem p, go::GameObject base);

		/**
		*Movimenta o inimigo na direção da "base" ou do "player", de acordo com a menor distância  
		*
		*@param p "player" ou jogador
		*@param base "base" do jogo
		*/
		void Mover(Player &p, go::GameObject base);

		/**
		* Retorna o dano causado pelos projéteis dos inimigos com o objeto enviado por parâmetro
		*
		* @param obj objeto
		*/
		int VerificarColisaoProjInimObj(const go::GameObject obj);

		/**
		* Faz a colisão entre os projéteis do Player com os Inimigos, 
		* calcula o dano, remove os inimigos derrotados e, se for o caso,
		* adiciona o drop à lista_cafe
		*
		* @param persona personagem cujo haverá verificação de colisão com seus projéteis (player)
		* @param &lista_cafe lista simplesmente encadeada enviada por referência. Novo drop poderá ser
		* adicionado a ela
		* @param sp_drop Recebe instância de classe que controlará sprites do objeto (drop)
		*/
		void VerificarColisaoProjPersInim(Personagem &persona, Lista<Drop*> &lista_cafe,
			SpManip::SpriteManip sp_drop);

		/**
		* Retorna se todos os inimigos e projéteis da Horda foram destruídos
		*
		*/
		bool Destruida();

		/**
		* Recebe o Id da horda atual
		*
		*/
		int GetId();

};

#endif
#ifndef _WAVES_H_
#define _WAVES_H_

#include "Horda.h"
#include "ListaEncadeada/lista.h"
#include "GameObject.h"
#include "Personagem.h"

/**
* \class Waves
*
* \brief Classe responsável por gerencia as Hordas
* 
*
*
*
*/

class Waves {

	private:
		//
		Horda* hordaAtual; /**< Aponta para a horda que está no campo de batalha */

		Lista<Horda*> *filaHorda; /**< É ponteiro para alterar valor da lista do local onde foi chamado,
		/* fazendo assim uma mudança nos dois locais. É necessário que o comportamento seja fila, 
		/* pelo fato de ser requerido no construtor */


		int tempoEspera; /**< É tempo de espera para a próxima horda, sendo medido em frames. 
		/* Se zero, a horda está na arena */


		Lista<int> *filaTempoEspera; /**< É ponteiro para alterar valor da lista do local onde foi chamado,
		/* fazendo assim uma mudança nos dois locais. É necessário que o comportamento seja fila, 
		/* pelo fato de ser requerido no construtor.
		/* Tal ponteiro armazena tempo de espera para aparecimento das próximas hordas (contidas na fila) */

	public:

		/**
		* Construtor padrão
		* 
		* Verifica se as duas listas se comportam como fila, se ambas tẽm o mesmo tamanho e se possuem algum elemento 
		* Além de salvar as filas nos ponteiros, atribui valor à variável "tempoEspera", e inicializar hordaAtual
		* O construtor exige que a fila de horda e a fila de tempo de espera tenham o mesmo tamanho
		*
		* @param fila_horda fila das hordas 
		* @param fila_tempo_espera  fila do tempo de espera
		*/
		Waves( Lista<Horda*> &fila_horda, Lista<int> &fila_tempo_espera );

		/**
		* Destrutor padrão
		*
		*
		*/
		~Waves();


		/**
		* Reduz tempo de espera, se o tempo for nulo será adicionada uma horda no campo de batalha
		* Retorna true caso esteja esperando, e false caso a horda esteja no campo de batalha
		*/
		bool EsperandoProximaHorda();

		/**
		* Retorna hordaAtual == NULL, caso a wave seja destruída
		* Assim, se hordaAtual apontar para nulo, significa que todas as hordas foram destruídas
		*/
		bool Destruida();

		/**
		* Movimenta os inimigos da horda atual, ou seja, da horda que estiver no campo de batalha
		*
		* @param p "player" ou jogdor
		* @param base "base" do jogo
		*/
		void Mover(Player &p, go::GameObject base);

		/**
		*  Faz com que inimigos da horda atual disparem
		*
		* @param p "personagem"
		* @param base "base" do jogo
		*/
		void Atirar(Personagem p, go::GameObject base);


		/**
		* Desenha os inimigos da horda, caso haja alguma horda no campo de batalha
		*
		*/
		void Draw();

		/**
		* Retorna o dano causado pelos projéteis dos inimigos com o objeto enviado por parâmetro
		*
		*
		* @param obj objeto
		*/
		int VerificarColisaoProjInimObj(const go::GameObject obj);

		/**
		* Faz colisão dos projéteis do player com os Inimigos, além de calcular o dano e remover os Inimigos derrotados
		*
		* @param persona "personagem"
		* @param lista_cafe lista que contêm os drops dos inimigos
		*/
		void VerificarColisaoProjPersInim(Personagem &persona, Lista<Drop*> &lista_cafe);

		/**
		* Retorna o id da horda atual
		*
		*/
		int GetIdHorda(); 

};

#endif
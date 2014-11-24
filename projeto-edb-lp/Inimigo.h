#ifndef _INIMIGO_H_
#define _INIMIGO_H_

#include "GameObject.h"
#include "ListaEncadeada/lista.h"
#include "Projetil.h"
#include "Personagem.h"
#include "Player.h"

/**
* \class Inimigo
*
* \brief Classe que representa o inimigo. Herda Personagem
*
*/

class Inimigo : public Personagem{

	#define INTERVALOTIROPADRAO 30 /**< Definição do intervalo padrao abaixo levou em conta 30 fps. */

	private:
		int Drop;  /**< Armazena a quantidade que vai ser dropado de energia */
		bool CalcularProxDest;
		int IntervaloTiro; /**< Armazena a quantidade em frames, entre os disparos de energia */
		int ProxTiro; /**< Armazena frames restantes para próximo tiro */
	public:
		/**
		* Método construtor que gera a posição inicial randomicamente, nas bordas
		* @param velocidade velocidade de movimento do Inimigo
		* @param vida vida do Inimigo
		*/
		Inimigo(int velocidade, int vida); 

		/**
		* Método construtor que inicializa o Inimigo completamente
		* @param velocidade velocidade de movimento do Inimigo
		* @param vida vida do Inimigo
		* @param raio Raio do Inimigo
		* @param intervalo_tiro Intervalo entre os disparos de energia, em frames
		* @param primeiro_tiro quantidade de frames até dar o primeiro disparo de energia
		* @param projetil_base Tipo da energia disparada pelo Inimigo
		* @param danoFisico Dano que será dado no Player caso se encostem
		*/
		Inimigo(int velocidade, int vida, int raio, int intervalo_tiro,
			int primeiro_tiro, Projetil projetil_base, int danoFisico);

		/**
		* Calcula se é o Player o Base que está mais proximo, e se move nessa direção;
		* @param p Player que será enviado
		* @param base Base que será enviada
		*/
		void Distancia(Personagem p, go::GameObject base);

		/**
		* Desenha na tela do Inimigo, chama o método  Personagem::Draw()
		*/
		void Draw();

		/**
		* Sobrecarga de operador, copia os valores do Personagem para Inimigo
		* @param persona Personagem que será copiado
		*/
		void operator=(const Personagem &persona);

		/**
		* Informa o novo destino que o Inimigo deve percorrer
		* @param DestinoX ponto X que ele deve ir
		* @param DestinoY ponto Y que ele deve ir
		*/
		void AtualizarDestino(unsigned int DestinoX, unsigned int DestinoY);

		/**
		* Realiza o disparo de energia do Inimigo
		* @param p Player que será enviado
		* @param base Base que será enviado
		*/
		void Atirar(const Personagem &p, const go::GameObject &base);

		/**
		* Sobrescreve operação de mover. Move tanto o player quanto suas balas
		*/
		void Mover();

		/**
		* Sobrescreve operação de mover. Move tanto o player quanto suas balas
		*/
		void Mover(Player &p, Inimigo &ini);

		/**
		* Sobrecarrega função Mover(). Move tanto o player quanto suas balas.
		* Só movimenta o personagem caso ele não tenha morrido e caso futura posição do personagem atual não
		* sobreponha nenhum porsonagem da lista.
		* @param &list_pers Lista simplesmente encadeada dos personagens a se verificar colisão futura
		* @param *This ponteiro do personagem atual presente em &list_pers
		*/
		void Mover(Lista<Personagem*> &list_pers, Personagem* This);
		
		/**
		* Verifica colisão entre Player e Inimigo, caso tenha o return 1, se não return 0
		* @param p Player a ser enviado
		* @param ini Inimigo a ser enviado
		* \return retorna 1 caso tenha colisão e 0 caso não tenha
		*/
		int VerificarColisaoInimigo(Player &p, Inimigo &ini);

		/**
		* Envia o valor do drop para Horda::VerificarColisaoProjPersInim()
		* \return Drop
		*/
		int Dropar();
};

#endif
#ifndef _DROP_H_
#define _DROP_H_

#include <allegro5/allegro.h> 
#include "GameObject.h"
#include "Player.h"
#include "ListaEncadeada/lista.h"

/**
* \class Drop
*
* \brief Classe que trata o drop do inimigo
*
* 
*
*/

class Drop : public go::GameObject{
	private:
		int energia; /**< Valor que será regenerado */  
		int tempoEspera; /**<  Tempo em fps que o drop ficará no jogo*/  

	public:
		/**
       * Construtor padrão
       * Chamado um vez em GameManager.cpp
       */
		Drop();

		/**
       * Construtor, inicializa os valores de energia, tempoEspera e origem do drop
       * @param energia valor de energia
       * @param XOrigem posição X em que ele aparecerá
       * @param YOrigem posição Y em que ele aparecerá
       */
		Drop(int energia, int XOrigem, int YOrigem);

		/**
		* Destrutor
		*/
		~Drop();

		/**
		* Sobrecarga do operador "=" copia os valores de GameObj para Drop
		* @param GameObj objeto a ser copiado
		*/
		void operator=(const GameObject &GameObj);

		/**
       * Desenha a lista de drop
       * @param &lista_cafe lista que fica armazenada todos os drop
       */
		void Draw(Lista<Drop*> &lista_cafe, ALLEGRO_DISPLAY *display); 

		/**
       * Regenera a energia do player, caso ele colida com o drop
       * @param p informações do player atual
       * @param lista_cafe lista com os drop
       */
		void Pegar(Player &p, Lista<Drop*> &lista_cafe); 

		/**
       * Verifica colisão entre player e um drop, retorna um valor inteiro
       * @param p informações do player atual
       * @param cafe um nó da lista_cafe
       * @return retorna 1 se ocorreu a colisão e 0 se não ocorreu
       */
		int VerificarColisao(Player &p, Drop &cafe); 

		/**
       * Retorna o valor da energia do drop
       * @return energia
       */
		int GetEnergia();

		/**
       * Decrementa o tempoEspera. Este metodo é chamado em Draw()
       * @return 1 se tempoEspera for maior que zero. 0 se tempoEspera for zero.
       */
		int PassarTempo();
};

#endif
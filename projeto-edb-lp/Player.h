#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Personagem.h"
#include "ListaEncadeada/lista.h"
#include "ListaEncadeada/FilaDupl.h"
#include "Projetil.h"
#include "SpriteManip.h"

/**
* \class Player
*
* \brief Classe que representa o jogador. Herda Personagem
*
*/

using namespace SpManip;

class Player : public Personagem {
private:

	int MaxEnergia; /**< Armazena a quantidade máxima de energia. */
	int EnergiaAtual; /**< Armazena a quantidade atual de energia, este valor é mostrado na tela. */
	int Regem; /**< Armazena taxa de regeneração.  */
	int VidaTotal; /**< Armazena a vida inicial do player. Necessário para garantir que o Regem não fique maior que a vida inicial. */
	FilaDupl<Projetil*> ataques;  /**< Armazena os diferentes tipos de ataques. */

public:
	/**
	* Construtor vazio
	*/
	Player();

	/**
	* Construtor completo
	* @param posicao_x posição x inicial do player
	* @param posição_y posição y inicial do player
	* @param max_energia atribui energia maxima ao player
	* @param energia_atual quantidade de energia a ser iniciado com o player
	* @param velocidade velocidade em fps que o player se movimentará
	* @param vida vida inicial do player
	* @param raio raio do player
	* @param regem taxa de regem que o player terá
	* @param projetil_base é o primeiro tipo de projetil que o player terá
	*/
	Player(unsigned int posicao_x, unsigned int posicao_y, int max_energia, int energia_atual, 
		int velocidade, int vida, int raio, int regem, Projetil projetil_base, SpriteManip sp_player,
		SpriteManip sp_proj1, SpriteManip sp_proj2, SpriteManip sp_proj3);

	/**
	* Sobrecarga de operador, copia os dados de persona para ele mesmo
	* @param persona Objeto a ser copiado
	*/
	void operator=(const Personagem &persona);

	/**
	* Método que recebe como parametro um inteiro e adiciona este valor a EnergiaAtual.
	* Chamado pelo método Drop.Pegar()
	* @param qtd Valor que será adicionado na EnergiaAtual
	*/
	void AdicionarEnergia(unsigned int qtd);


	/**
	* Método que realiza o disparo de energia, recebe como parametros as posições XY e decrementa a EnergiaAtual
	* @param destino_x posição X do mouse
	* @param destino_y posição Y do mouse
	*/
	void Atirar(unsigned int destino_x, unsigned int destino_y);

	/**
	* Desenha o player, chama o metodo Draw de Personagem
	*/
	void Draw();

	/**
	* Aumenta o valor de Vida baseado em Regem e não deixa ser maior que VidaTotal
	*/
	void Regenerar();

	/**
	* Avança para o próximo tipo de ataque
	*/
	void ProxProjetil(); 

	/**
	* Volta para o ataque anterior
	*/
	void AntProjetil(); 

	/**
	* Cria a lista com os ataques do Player, é chamado no construtor de Player
	*/
	void SalvarAtaques(SpriteManip sp_proj1, SpriteManip sp_proj2, SpriteManip sp_proj3); 

	/**
	* Retorna EnergiaAtual, método chamado para mostrar na tela o valor da energia do Player
	*/
	int GetEnergiaAtual();
};

#endif

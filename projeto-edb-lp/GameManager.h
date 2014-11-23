#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include <allegro5/allegro.h>
#include <string>

/**
* \class GameManager
*
* \brief Classe que gerencia o Jogo
*
* 
*
*/

class GameManager
{

public:

	/**
       * Construtor padrão
       * Chamado para gerar o Objeto da Classe "Jogo" em BaseDefender.cpp
       */

	GameManager();

	/**
	* Executa o Jogo
	* @param event_queue ponteiro que recebe a "fila do evento"
	* @param ev objeto passado por referência para manter os dados de qualquer tipo de eventos
	* @param display ponteiro que representa uma janela aberta. Recebido para que a tela do jogo seja desenhada
	* @param timer ponteiro que representa um tipo abstrato de dado temporizador
	* @param max_largura parâmetro que determina a largura do display. Utilizado pelo o objeto "arena" do tipo GameObject em GameManager.cpp
	* @param max_altura parâmetro que determina a altura do display. Utilizado pelo o objeto "arena" do tipo GameObject em GameManager.cpp


   */


	int Executar(ALLEGRO_EVENT_QUEUE * event_queue,  ALLEGRO_EVENT &ev, ALLEGRO_DISPLAY *display,
	ALLEGRO_TIMER *timer, int max_largura, int max_altura);

	/**
	* Checa se uma expressão foi inicializada. Se não, é impressa uma mensagem de erro
	* @param expression variável booleana que recebe a expressão a ser checada
	* @param message variável do tipo string que recebe a mensagem a ser impressa em caso de erro
	
   */

	void checkExpression (bool expression, std::string message);

};

#endif
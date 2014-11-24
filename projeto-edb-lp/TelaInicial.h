#ifndef _TELAINICIAL_H_
#define _TELAINICIAL_H_


/**
* \class TelaInicial
*
* \brief Classe que gera a tela de Menu
*
* 
*
*/

class TelaInicial 
{

public:

	/**
	* Construtor padrão
	* Chamado para gerar um objeto denominado "Menu" em BaseDefender.cpp
	*/

	TelaInicial();

	/**
	* Destrutor padrão
	*
	*/
	~TelaInicial();

	/**
	* Executa a tela de Menu
	* @param event_queue ponteiro que recebe a "fila do evento"
	* @param ev objeto passado por referência para manter os dados de qualquer tipo de eventos
	* @param display ponteiro que representa uma janela aberta. Recebido para que a tela de Menu seja desenhada

   */

	int Executar( ALLEGRO_EVENT_QUEUE * event_queue,  ALLEGRO_EVENT &ev, ALLEGRO_DISPLAY *display);


};


#endif
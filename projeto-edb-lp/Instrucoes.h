#ifndef _INSTRUCOES_
#define _INSTRUCOES_

/**
* \class Instrucoes
*
* \brief Classe que gera a tela de Intruções
*
* 
*
*/

class Instrucoes
{

public:

	/**
	* Construtor padrão
	* Chamado para gerar um objeto denominado "Instrucao" em BaseDefender.cpp
	*/
	Instrucoes();

	/**
	* Executa a tela de instruções
	* @param event_queue ponteiro que recebe a "fila do evento"
	* @param ev objeto passado por referência para manter os dados de qualquer tipo de eventos
	* @param display ponteiro que representa uma janela aberta. Recebido para que a tela de Instruções seja desenhada
    */
	int Executar(ALLEGRO_EVENT_QUEUE * event_queue,  ALLEGRO_EVENT &ev, ALLEGRO_DISPLAY *display);
};

#endif
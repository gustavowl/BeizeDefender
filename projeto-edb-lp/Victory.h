#ifndef _VICTORY_
#define _VICTORY_

/**
* \class Victory
*
* \brief Classe que gera a tela de Vitória
*
* 
*
*/

class Victory
{

public:

	/**
	* Construtor padrão
	* Chamado para gerar um objeto denominado "Vitoria" em BaseDefender.cpp
	*/

	Victory();

	/**
   * Gera a tela de Vitória
   * @param display ponteiro que representa uma janela aberta. Recebido para que a tela de Vitória seja desenhada
   */

	int Executar( ALLEGRO_DISPLAY *display );


};

#endif
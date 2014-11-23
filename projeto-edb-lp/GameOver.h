#ifndef _GAME_OVER_
#define _GAME_OVER_

/**
* \class GameOver
*
* \brief Classe que gera a tela de GameOver
*
* 
*
*/

class GameOver
{

public:


	/**
	* Construtor padrão
	* Chamado para gerar um objeto denominado "Fim" em BaseDefender.cpp
	*/

	GameOver();

	/**
	* Gera a tela de GameOver
	* @param display ponteiro que representa uma janela aberta. Recebido para que a tela de GameOver seja desenhada
	*/

	int Executar( ALLEGRO_DISPLAY *display );


};

#endif
#ifndef __CREDITOS_
#define __CREDITOS_

#include <string>

/**
* \class Creditos
*
* \brief Classe que gera a tela de CrÃ©ditos
*
* 
*
*/

class Creditos
{

public:

	/**
	* Construtor padrÃ£o
	* Chamado para gerar um objeto denominado "Credito" em BaseDefender.cpp
	*/
	Creditos();

	/**
	* Destrutor padrÃ£o
	*/	
	~Creditos();

	/**
	* Gera a tela de Credito
	* @param display ponteiro que representa uma janela aberta. Recebido para que a tela de Credito seja desenhada
	*/
	int Executar( ALLEGRO_DISPLAY *display );


	/**
	* Checa se uma expressÃ£o foi inicializada. Se nÃ£o, Ã© impressa uma mensagem de erro
	* @param expression variÃ¡vel booleana que recebe a expressÃ£o a ser checada
	* @param message variÃ¡vel do tipo string que recebe a mensagem a ser impressa em caso de erro
    */
	void checkExpression (bool expression, std::string message);
};

#endif
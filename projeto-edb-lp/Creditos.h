#ifndef __CREDITOS_
#define __CREDITOS_

#include <string>

/**
* \class Creditos
*
* \brief Classe que gera a tela de Créditos
*
* 
*
*/

class Creditos
{

public:

	/**
	* Construtor padrão
	* Chamado para gerar um objeto denominado "Credito" em BaseDefender.cpp
	*/
	Creditos();

	/**
	* Destrutor padrão
	*/	
	~Creditos();

	/**
	* Gera a tela de Credito
	* @param display ponteiro que representa uma janela aberta. Recebido para que a tela de Credito seja desenhada
	*/
	int Executar( ALLEGRO_DISPLAY *display );


	/**
	* Checa se uma expressão foi inicializada. Se não, é impressa uma mensagem de erro
	* @param expression variável booleana que recebe a expressão a ser checada
	* @param message variável do tipo string que recebe a mensagem a ser impressa em caso de erro
    */
	void checkExpression (bool expression, std::string message);
};

#endif
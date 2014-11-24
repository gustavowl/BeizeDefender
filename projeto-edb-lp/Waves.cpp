#include "Waves.h"
#include <cstddef> 

Waves::Waves( Lista<Horda*> &fila_horda, Lista<int> &fila_tempo_espera ) 
{
	/*Garante valores iniciais válidos*/

	hordaAtual = NULL;
	tempoEspera = 0;

	/* Verifica se as duas listas se comportam como fila, se tẽm o mesmo tamanho e se possuem algum elemento */

	if ( fila_horda.GetBehavior() == FILA && fila_tempo_espera.GetBehavior() == FILA &&
		fila_horda.Size() == fila_tempo_espera.Size() && fila_horda.Size() > 0 ) {

		//Salva filas nos ponteiros
		filaHorda = &fila_horda;
		filaTempoEspera = &fila_tempo_espera;

		//Atribui valor a tempoEspera e remove um elemento da fila de tempo de espera
		filaTempoEspera->Remove( tempoEspera );

		//Atribui valor válido caso necessário
		if (tempoEspera < 0)
			tempoEspera = 0;

		//Inicializa hordaAtual
		filaHorda->Remove(hordaAtual);
	}

}

Waves::~Waves() 
{
	if ( hordaAtual != NULL )
		delete hordaAtual;

	//Remove todos os elementos da lista
	while ( filaHorda->Remove(hordaAtual) ) 
	//Desaloca todos os elementos dinamicamente alocados
		delete hordaAtual;
	//Chamando destrutor para fila de inteiros para que fila original esteja zerada, que nem a fila de horda
	while ( filaTempoEspera->Remove() );
}

bool Waves::EsperandoProximaHorda() {
	if ( tempoEspera > 0 ) {
		tempoEspera--;
		return true;
	}
	return false;
}

bool Waves::Destruida() 
{ 
	return hordaAtual == NULL;
}

void Waves::Mover(Player &p, go::GameObject base) 
{
	//Move caso haja uma horda no campo de batalha
	if ( hordaAtual != NULL && tempoEspera == 0 )
		hordaAtual->Mover(p, base);
}

void Waves::Atirar(Personagem p, go::GameObject base) 
{
	//atira caso haja uma horda no campo de batalha
	if ( hordaAtual != NULL && tempoEspera == 0 )
		hordaAtual->Atirar(p, base);
}

void Waves::Draw() 
{
	//Desenha caso haja uma horda no campo de batalha
	if ( hordaAtual != NULL && tempoEspera == 0 )
		hordaAtual->Draw();
}

int Waves::VerificarColisaoProjInimObj(const go::GameObject obj) {
	if ( hordaAtual != NULL && tempoEspera == 0 )
		return hordaAtual->VerificarColisaoProjInimObj(obj);
	return 0;
}


void Waves::VerificarColisaoProjPersInim(Personagem &persona, Lista<Drop*> &lista_cafe) {
	if ( hordaAtual != NULL && tempoEspera == 0 ) {
		//Calcula todo o dano
		hordaAtual->VerificarColisaoProjPersInim(persona, lista_cafe);
		//Verifica se horda foi destruída
		if ( hordaAtual->Destruida() ) { 
			delete hordaAtual; //Deleta horda dinamicamente alocada
			//Verifica se ainda há hordas restantes
			if ( filaTempoEspera->Size() > 0 ) {
				//Atualiza valores para próxima horda
				filaHorda->Remove(hordaAtual);
				filaTempoEspera->Remove(tempoEspera);
			}
			else //Faz com que hordaAtual não aponte pra nada
				hordaAtual = NULL;
		}
	}
}

int Waves::GetIdHorda(){
	if(hordaAtual != NULL){
		return hordaAtual->GetId();	
	}
	return 0;
}
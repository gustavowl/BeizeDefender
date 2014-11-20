#include "Waves.h"
#include <cstddef> //para NULL

//exige fila de horda e de tempo de espera com o mesmo tamanho
Waves::Waves( Lista<Horda*> &fila_horda, Lista<int> &fila_tempo_espera ) {
	//garante valores iniciais válidos
	hordaAtual = NULL;
	tempoEspera = 0;
	//verifica se as duas listas se comportam como fila, se tẽm o mesmo tamanho e se possuem algum elemento
	if ( fila_horda.GetBehavior() == FILA && fila_tempo_espera.GetBehavior() == FILA &&
		fila_horda.Size() == fila_tempo_espera.Size() && fila_horda.Size() > 0 ) {
		//salva filas nos ponteiros
		filaHorda = &fila_horda;
		filaTempoEspera = &fila_tempo_espera;
		//atribui valor a tempoEspera e remove um elemento da fila de tempo de espera
		filaTempoEspera->Remove( tempoEspera );
		//atribui valor válido caso necessário
		if (tempoEspera < 0)
			tempoEspera = 0;
		//inicializa hordaAtual
		filaHorda->Remove(hordaAtual);
	}

}

Waves::~Waves() {
	if ( hordaAtual != NULL )
		delete hordaAtual;
	//remove todos os elementos da lista
	while ( filaHorda->Remove(hordaAtual) ) //pode colocar dentro do if acima? (creio q sim)
		//desaloca todos os elementos dinamicamente alocados
		delete hordaAtual;
	//chamando destrutor para fila de inteiros para que fila original esteja zerada, que nem a fila de horda
	while ( filaTempoEspera->Remove() );
	//acho que não precisa chamar o destrutor da lista de inteiros por causa do destrutor de lista.h
}

//reduz tempo de espera, se tempo = 0 adiciona horda no campo de batalha
bool Waves::EsperandoProximaHorda() {
	if ( tempoEspera > 0 ) {
		tempoEspera--;
		return true;
	}
	return false;
}

bool Waves::Destruida() { //retorna se a wave foi destruída
	//se hordaAtual apontar para nulo, todas as hordas foram destruídas
	return hordaAtual == NULL;
}

//faz com que inimigos da horda atual se movam
void Waves::Mover(Personagem p, go::GameObject base) {
	//move caso haja uma horda no campo de batalha
	if ( hordaAtual != NULL && tempoEspera == 0 )
		hordaAtual->Mover(p, base);
}

//Faz com que inimigos da horda atual atirem
void Waves::Atirar(Personagem p, go::GameObject base) {
	//atira caso haja uma horda no campo de batalha
	if ( hordaAtual != NULL && tempoEspera == 0 )
		hordaAtual->Atirar(p, base);
}

void Waves::Draw() {
	//desenha caso haja uma horda no campo de batalha
	if ( hordaAtual != NULL && tempoEspera == 0 )
		hordaAtual->Draw();
}

//retorna dano causado pelos projéteis dos inimigos em obj
int Waves::VerificarColisaoProjInimObj(const go::GameObject obj) {
	if ( hordaAtual != NULL && tempoEspera == 0 )
		return hordaAtual->VerificarColisaoProjInimObj(obj);
	return 0;
}

/*Faz colisão dos projéteis de persona com Inimigos, calcula dano
e remove inimigos derrotados*/
void Waves::VerificarColisaoProjPersInim(Personagem &persona) {
	if ( hordaAtual != NULL && tempoEspera == 0 ) {
		//calcula todo o dano
		hordaAtual->VerificarColisaoProjPersInim(persona);
		//verifica se horda foi destruída
		if ( hordaAtual->Destruida() ) { //colocar para destruir só se todas as balas foram destruidas
			delete hordaAtual; //deleta horda dinamicamente alocada
			//verifica se ainda há hordas restantes
			if ( filaTempoEspera->Size() > 0 ) {
				//atualiza valores para próxima horda
				filaHorda->Remove(hordaAtual);
				filaTempoEspera->Remove(tempoEspera);
			}
			else //faz com que hordaAtual não aponte pra nada
				hordaAtual = NULL;
		}
	}
}
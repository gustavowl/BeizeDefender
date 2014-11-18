#include "Horda.h"
#include "Inimigo.h"


Horda::Horda(int quantidade, int id){
	this->quantInimigos = quantidade;
	this->id = id;

	for (int i = 0; i < quantidade; ++i){
		Inimigo *enemy = new Inimigo(2, 5);
		listaInimigos.Insert(0, enemy);
	}	
}

void Horda::LiberarInimigos(){
	Inimigo *temp;
	int i = 0;
	while(listaInimigos.GetElem(i, temp)){
		temp->Draw();
		i++;
	}
}

void Horda::Mover(Personagem p, int base_raio){

	Inimigo *temp;
	int i = 0;
	while(listaInimigos.GetElem(i, temp)){
		temp->Distancia(p, base_raio);
		temp->Mover();
		i++;
	}
/*
	Projetil *temp1;  i = 0;
	while ( Projeteis.GetElem( i, temp1 ) ) {
		temp1->Mover();
		i++;
	}*/
}
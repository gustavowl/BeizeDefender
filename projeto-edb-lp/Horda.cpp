#include "Horda.h"
#include "Inimigo.h"
#include "GameObject.h"


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
		
		//temp->

		i++;
	}
/*
	Projetil *proj_temp;  i = 0;
	while ( Projeteis.GetElem( i, proj_temp ) ) {
		proj_temp->Mover();
		i++;
	}*/
}

void Horda::Atirar(Personagem p){
	Inimigo *temp;
	
	int i = 0;
	while(listaInimigos.GetElem(i, temp)){
		temp->Atirar(p);
		i++;
	}
}

int Horda::VerificarColisao(const go::GameObject obj) { //retorna dano causado pelas balas ao obj, e destrói

	Inimigo *ini_temp;
	int i = 0;
	int dano_total = 0;
	while(listaInimigos.GetElem(i, ini_temp)){
		dano_total += ini_temp->VerificarColisao(obj);
		i++;
	}
	//projéteis que causaram dano. Função exterior tem q tirar vida do obj
	//pega informações para calcular colisão de objeto
    return dano_total;
}
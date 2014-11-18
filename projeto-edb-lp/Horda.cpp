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

Horda::~Horda() {
	Inimigo *ini_temp;
	int i = 0;
	while(listaInimigos.GetElem(i, ini_temp)) {
		listaInimigos.Remove(i); //remove inimigo da lista (acho q n precisa por causa do destrutor da lista)
		delete ini_temp; //deleta instância de inimigo dinamicamente alocada
	}
}

void Horda::Draw(){
	Inimigo *temp;
	int i = 0;
	while(listaInimigos.GetElem(i, temp)){
		temp->Draw();
		i++;
	}
}

void Horda::Mover(Personagem p, go::GameObject base){

	Inimigo *temp;
	int i = 0;
	while(listaInimigos.GetElem(i, temp)){
		temp->Distancia(p, base);
		temp->Mover();
		i++;
	}
}

void Horda::Atirar(Personagem p){
	Inimigo *temp;
	
	int i = 0;
	while(listaInimigos.GetElem(i, temp)){
		temp->Atirar(p);
		i++;
	}
}

//retorna dano causado pelas balas
int Horda::VerificarColisaoProjInimObj(const go::GameObject obj) {
	Inimigo *ini_temp;
	int i = 0;
	int dano_total = 0;
	while(listaInimigos.GetElem(i, ini_temp)){
		dano_total += ini_temp->VerificarColisao(obj);
		i++;
	}
    return dano_total;
}

void Horda::VerificarColisaoProjPersInim(Personagem &persona) {
	Inimigo *ini_temp;
	int i = 0;
	int dano_total = 0;
	while (listaInimigos.GetElem(i, ini_temp)) {
		ini_temp->LevarDano( persona.VerificarColisao(*ini_temp) );
		if ( ini_temp->GetVida() > 0 ) //se não morreu
			i++; //verifica colisão com próximo inimigo
		else {//se morreu
			 //remove inimigo da lista, não incrementa o i pois verifica próximo inimigo
			listaInimigos.Remove(i);
			delete ini_temp; //deleta instância de inimigo dinamicamente alocada
		}
	}
}

bool Horda::Destruida() {
	if ( listaInimigos.Size() > 0 ) //se tamanho == 0, destruiu todos
		return false;
	return true;
}
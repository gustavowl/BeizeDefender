#include "Drop.h"
#include "Horda.h"
#include "Inimigo.h"
#include "GameObject.h"
#include <stdlib.h>
#include <time.h>


Horda::Horda(int quantidade) {
	if (quantidade > 0) {
		for (int i = 0; i < quantidade; ++i){
			Inimigo *enemy = new Inimigo(2, 5); //cria inimigo padrão
			listaInimigos.Insert(0, enemy);
		}
	}

}

Horda::Horda(int idHorda, int quantidade, int velocidade, int vida, int raio, int municao, int intervelo_tiro,
	int primeiro_tiro, Projetil projetil_base) {
	id = idHorda;
	if (quantidade > 0) {
		for (int i = 0; i < quantidade; ++i){
			Inimigo *enemy = new Inimigo(velocidade, vida, raio, municao, intervelo_tiro,
				primeiro_tiro, projetil_base);
			listaInimigos.Insert(0, enemy);
		}
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

void Horda::Atirar(Personagem p, go::GameObject base) {
	Inimigo *temp;
	
	int i = 0;
	while(listaInimigos.GetElem(i, temp)){
		temp->Atirar(p, base);
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

void Horda::VerificarColisaoProjPersInim(Personagem &persona, Lista<Drop*> &fila_cafe) {
	Inimigo *ini_temp;
	int i = 0;
	int dano_total = 0;
	while (listaInimigos.GetElem(i, ini_temp)) {
		ini_temp->LevarDano( persona.VerificarColisao(*ini_temp) );
		//se não foi totalmente destruído (ele e projéteis)
		if ( !ini_temp->PersonagemEProjeteisDestruidos() )
			i++; //verifica colisão com próximo inimigo
		else {//se morreu
			 //remove inimigo da lista, não incrementa o i pois verifica próximo inimigo
			srand (time (NULL)); // Gera uma 'random seed' baseada no retorno da funcao time()
			int numero;
			numero = (rand () % 3) + 1; // Retorna um numero aleatorio entre 1 e 4
			if(numero == 1){ // Chance de 25% para realizar o drop
				Drop *cafe_temp = new Drop(ini_temp->Dropar(), ini_temp->GetXAtual(), ini_temp->GetYAtual());
				fila_cafe.Insert(0, cafe_temp);	
				std::cout<<ini_temp->Dropar()<<std::endl;
			}
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

int Horda::GetId(){
	return id;
}
#include "Drop.h"
#include "Horda.h"
#include "Inimigo.h"
#include "GameObject.h"
#include <cstdlib>
#include <ctime>


Horda::Horda(int quantidade) {
	if (quantidade > 0) {
		for (int i = 0; i < quantidade; ++i){
			Inimigo *enemy = new Inimigo(2, 5); //Cria inimigo padrão
			listaInimigos.Insert(0, enemy);
		}
	}

}

Horda::Horda(int idHorda, int quantidade, int velocidade, int vida, int raio, int municao, int intervalo_tiro,
	int primeiro_tiro, Projetil projetil_base, int danoFisico) {
	id = idHorda;
	if (quantidade > 0) {
		for (int i = 0; i < quantidade; ++i){
			Inimigo *enemy = new Inimigo(velocidade, vida, raio, intervalo_tiro,
				primeiro_tiro, projetil_base, danoFisico);
			listaInimigos.Insert(0, enemy);
		}
	}
}

Horda::~Horda() {
	Inimigo *ini_temp;
	int i = 0;
	while(listaInimigos.GetElem(i, ini_temp)) {
		listaInimigos.Remove(i); //Remove inimigo da lista (acho q n precisa por causa do destrutor da lista)
		delete ini_temp; //Deleta instância de inimigo dinamicamente alocada
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

void Horda::Mover(Player &p, go::GameObject base){

	Lista<Personagem*> lista_p; 
	Personagem *p_temp;
	Inimigo *temp;
	int i = 0;
	while(listaInimigos.GetElem(i, temp)) {
		p_temp = new Personagem();
		*p_temp = *temp;
		lista_p.Insert(i, p_temp);
		i++;
	}
	i = 0;
	while(listaInimigos.GetElem(i, temp)) {
		lista_p.GetElem(i, p_temp);
 		temp->Distancia(p, base);
		temp->Mover(lista_p, p_temp);
		if(temp->VerificarColisaoInimigo(p, *temp)){
			temp->LevarDano(p.GetDanoFisico());
			p.LevarDano(temp->GetDanoFisico());
		}
 		i++;
 	}
 	while (lista_p.Remove(0, p_temp)) {
		delete p_temp;
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
		//Se não foi totalmente destruído (ele e projéteis)
		if ( !ini_temp->PersonagemEProjeteisDestruidos() )
			i++; //Verifica colisão com próximo inimigo
		else {//Se morreu
			 //Remove inimigo da lista, não incrementa o i pois verifica próximo inimigo
			srand (time (NULL)); // Gera uma 'random seed' baseada no retorno da funcao time()
			int numero;
			numero = (rand () % 3) + 1; // Retorna um numero aleatorio entre 1 e 4
			if(numero == 1){ // Chance de 25% para realizar o drop
				Drop *cafe_temp = new Drop(ini_temp->Dropar(), ini_temp->GetXAtual(), ini_temp->GetYAtual());
				fila_cafe.Insert(0, cafe_temp);	
			}
			listaInimigos.Remove(i);
			delete ini_temp; //deleta instância de inimigo dinamicamente alocada
		}
	}
}

bool Horda::Destruida() {
	if ( listaInimigos.Size() > 0 ) //Se tamanho == 0, destroi todos
		return false;
	return true;
}

int Horda::GetId(){
	return id;
}
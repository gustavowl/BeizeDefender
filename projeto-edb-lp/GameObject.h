#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

namespace {

enum WalkType { STATIC, LINEAR, SMOOTH };

class GameObject {
	private:
		static unsigned int MaxX; //define tamanho da arena
		static unsigned int MaxY; //define tamanho da arena

	protected:

		unsigned int XOrigem; //posição de Origem //usado para calcular interpolação linear
		unsigned int YOrigem; //posição de Origem //usado para calcular interpolação linear

		unsigned int XAtual; //posição atual (Utilizado para detectar colisão)
		unsigned int YAtual; //posição atual (Utilizado para detectar colisão)

		unsigned int XDestino; //posição de destino
		unsigned int YDestino; //posição de destino

		unsigned int Raio; //para detectar colisões
		unsigned int Velocidade; //velocidade em pixel/s

		WalkType TipoMovimento;

		virtual void Mover(); //atualiza posição atual, leva em conta a velocidade
		unsigned int GetMaxX();
		unsigned int GetMaxY();

	public:
		GameObject(); //cria "objeto vazio"
		GameObject(unsigned int MaximoX, unsigned int MaximoY); //inicializa tamanho da arena, só permite alterar o tamanho uma vez
		GameObject(unsigned int Velocidade, unsigned int Raio, WalkType TipoMov); //pode gerar posição inicial randômica
		GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, unsigned int Raio, WalkType TipoMov);
		GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, 
			unsigned int DestinoX, unsigned int DestinoY, unsigned int Raio, WalkType TipoMov);
		~GameObject();
};

unsigned int GameObject::MaxY = 0;
unsigned int GameObject::MaxX = 0;
}

#endif
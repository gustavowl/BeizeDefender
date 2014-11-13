#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

class GameObject {
	private:
		static unsigned int MaxX = 0; //define tamanho da arena
		static unsigned int MaxY = 0; //define tamanho da arena


	protected:
		unsigned int PosicaoX; //posição atual (ponto de origem)
		unsigned int PosicaoY; //posição atual (ponto de origem)
		unsigned int Raio; //para detectar colisões
		unsigned int Velocidade; //velocidade em pixel/s
		unsigned int DestinoX; //posição de destino
		unsigned int DestinoY; //posição de destino

		virtual void Mover(); //atualiza posição atual, leva em conta a velocidade
		unsigned int GetMaxX();
		unsigned int GetMaxY();

	public:
		GameObject(); //cria "objeto vazio"
		GameObject(unsigned int MaximoX, unsigned int MaximoY); //gera posição inicial randômica
		//só permite alterar o tamanho da arena uma vez e ao criar um objeto tipo GameObject (não herdados)
		GameObject(unsigned int Velocidade, unsigned int Raio); //gera posição inicial randômica
		GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, unsigned int Raio);
		GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, 
			unsigned int DestinoX, unsigned int DestinoY, unsigned int Raio);
		~GameObject();
};

#endif
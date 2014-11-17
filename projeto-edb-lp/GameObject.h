#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

enum WalkType { STATIC, LINEAR, SMOOTH };
/**/
namespace go {

class GameObject {
	protected:
		static unsigned int MaxX; //define tamanho da arena
		static unsigned int MaxY; //define tamanho da arena
		unsigned int FrameAtual = 0; //Frame atual da interpolação
		unsigned int TotalFrames = 0; //quantidade de frames necessários para atingir o destino

		unsigned int XOrigem; //posição de Origem //usado para calcular interpolação linear
		unsigned int YOrigem; //posição de Origem //usado para calcular interpolação linear

		unsigned int XAtual; //posição atual (Utilizado para detectar colisão)
		unsigned int YAtual; //posição atual (Utilizado para detectar colisão)

		unsigned int XDestino; //posição de destino
		unsigned int YDestino; //posição de destino

		unsigned int Raio; //para detectar colisões
		unsigned int Velocidade; //velocidade em pixel/s

		WalkType TipoMovimento;

	public:
		virtual void Mover(); //atualiza posição atual, leva em conta a velocidade. Deve ser chamada a cada frame
		virtual void AtualizarDestino(unsigned int DestinoX, unsigned int DestinoY);
		unsigned int GetMaxX() const;
		unsigned int GetMaxY() const;
		void GetPosicaoAtual(unsigned int &x, unsigned int &y) const;
		unsigned int GetXAtual() const;
		unsigned int GetYAtual() const;
		unsigned int GetFrameAtual() const;
		unsigned int GetTotalFrames() const;
		unsigned int GetXOrigem() const;
		unsigned int GetYOrigem() const;
		unsigned int GetXDestino() const;
		unsigned int GetYDestino() const;
		unsigned int GetRaio() const;
		unsigned int GetVelocidade() const;
		WalkType GetTipoMovimento() const;

		GameObject(); //cria "objeto vazio"
		GameObject(unsigned int MaximoX, unsigned int MaximoY); //inicializa tamanho da arena, só permite alterar o tamanho uma vez
		GameObject(unsigned int Velocidade, unsigned int Raio, WalkType TipoMov); //gera posição inicial randômica nas bordas
		GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, unsigned int Raio, WalkType TipoMov);
		GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, 
			unsigned int DestinoX, unsigned int DestinoY, unsigned int Raio, WalkType TipoMov);
		~GameObject();
};

//unsigned int GameObject::MaxY = 0;
//unsigned int GameObject::MaxX = 0;

}

#endif
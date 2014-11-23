#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include <allegro5/allegro.h>
#include <string>

class GameManager
{

public:

	GameManager();
	int Executar(ALLEGRO_EVENT_QUEUE * event_queue,  ALLEGRO_EVENT &ev, ALLEGRO_DISPLAY *display,
	ALLEGRO_TIMER *timer, int max_largura, int max_altura);
	void checkExpression (bool expression, std::string message);

};

#endif
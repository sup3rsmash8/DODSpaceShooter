#pragma once
#include <map>
#include "GameEngine.h"
#include "GameBase.h"

class Statics final
{
	friend class GameEngine;
private:
	/* The first registered game engine. */
	static GameEngine* m_gameEngine;

public:
	/* Returns the game engine currently being run in the game. */
	static GameEngine* GetGameEngine();

	/* Returns the game base contained by the game engine. */
	static GameBase* GetGameBase();

	/* Returns the room view of the current room. Returns (0, 0, 0, 0) if room or game base is null. */
	static SDL_Rect GetRoomView();
};
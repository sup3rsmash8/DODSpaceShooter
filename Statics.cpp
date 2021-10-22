#include "Statics.h"
#include "GameEngine.h"
#include "GameBase.h"

GameEngine* Statics::m_gameEngine = nullptr;

GameEngine* Statics::GetGameEngine()
{
    return m_gameEngine;
}

GameBase* Statics::GetGameBase()
{
    const GameEngine* gameEngine = GetGameEngine();
    if (!gameEngine)
        return nullptr;

    return gameEngine->GetGameBase();
}

SDL_Rect Statics::GetRoomView()
{
	GameBase* gameBase = GetGameBase();

	if (gameBase)
	{
		Room* room = gameBase->GetRoom();
		if (room)
		{
			return room->GetRoomView();
		}
	}

    return SDL_Rect();
}

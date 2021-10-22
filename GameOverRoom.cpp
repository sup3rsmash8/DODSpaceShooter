#include "GameOverRoom.h"

#include "GameOverScreen.h"

const std::string GameOverRoom::m_roomName = "TestLevel";

std::map<GameObjectID, std::vector<GameObject*>> GameOverRoom::InitRoomObjects()
{
    std::map<GameObjectID, std::vector<GameObject*>> initObjects = std::map<GameObjectID, std::vector<GameObject*>>();

    GameOver* gameOverScreen = new GameOver({ 400, 300 });

    const GameObjectID id = gameOverScreen->GetID();

    initObjects.emplace(id, std::vector<GameObject*>{ gameOverScreen });

    return initObjects;
}

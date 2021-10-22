#include "TestLevel.h"

#include "SpaceShip.h"
//#include "EnemyAsteroid.h"
#include "TextObject.h"
#include "Statics.h"
#include "SpaceShooterGame.h"
//#include "EnemySpaceShip.h"
#include "WaveSpawner.h"

#include "GameUI.h"

const std::string TestLevel::m_roomName = "TestLevel";

std::map<GameObjectID, std::vector<GameObject*>> TestLevel::InitRoomObjects()
{
    std::map<GameObjectID, std::vector<GameObject*>> initObjects = std::map<GameObjectID, std::vector<GameObject*>>();

    SpaceShip* player = new SpaceShip(Vector2(400, 300), 0, true);

    initObjects.emplace(player->GetID(), std::vector<GameObject*> { player });

    SpaceShooterGame* game = (SpaceShooterGame*)Statics::GetGameBase();

    // NOTE: ALL GameObjects supposed to spawn on room load must be 
    // added to initObjects (even the ones created in object constructors), so make sure 
    // they're added/accessible here, otherwise they'll not be recognized by the game base!
    if (game)
    {
        //initObjects.push_back(new TextObject(Vector2(400, 32), 0, true, "FOX News", game->GetStandardFont()));
        
        TextObject* livesLabel;
        TextObject* livesCount;
        TextObject* scoreLabel;
        TextObject* scoreCount;
        
        GameUI* gameUI = new GameUI(VEC2_ZERO, 0, true, static_cast<PlayerObject*>(player));

        initObjects.emplace(gameUI->GetID(), std::vector<GameObject*> { gameUI });

        gameUI->GetTextObjects(livesLabel, livesCount, scoreLabel, scoreCount);
        std::vector<GameObject*> textObjects
        {
            livesLabel,
            livesCount,
            scoreLabel,
            scoreCount
        };
        initObjects.emplace(GameObjectID::TEXT_OBJECT, textObjects);

        EnemyAsteroid* testAsteroid = new EnemyAsteroid(Vector2(720, 300), 0, true);
        initObjects.emplace(GameObjectID::ASTEROID, std::vector<GameObject*> { testAsteroid });

        EnemySpaceShip* testEnemyShip = new EnemySpaceShip(MovePattern::MOVE_STOP_MOVE, { 800, 300 });
        initObjects.emplace(GameObjectID::ENEMY_SHIP, std::vector<GameObject*> { testEnemyShip });

        WaveSpawner* testWaveSpawner = new WaveSpawner({ 400, 600 });
        initObjects.emplace(testWaveSpawner->GetID(), std::vector<GameObject*> { testWaveSpawner });
    }

    return initObjects;
}

void TestLevel::OnRoomLoad()
{
    Room::OnRoomLoad();

    Vector2 resolution;

    GameBase* gameBase = Statics::GetGameBase();
    if (gameBase)
    {
        resolution = gameBase->GetScreenResolution();
    }
    else
    {
        resolution = VEC2_ZERO;
    }

    SDL_Rect rect = { 0, 0, (int)resolution.x, (int)resolution.y };

    SetRoomView(rect);
}

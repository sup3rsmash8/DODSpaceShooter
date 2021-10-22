#include "SpaceShooterGame.h"
#include "GameBase.h"
#include "TestLevel.h"
#include "GameOverRoom.h"

#include "SpaceShooterGameObject.h"
#include "GameObjectID.h"

//dbg
#include <iostream>

const std::string SpaceShooterGame::m_gameName = "SpaceShooter";

MulticastFunction<Uint32> SpaceShooterGame::m_onNewScoreSet = MulticastFunction<Uint32>();

std::vector<Room*> SpaceShooterGame::m_gameRooms = std::vector<Room*>
{
    new TestLevel(), // RoomID::MAIN_GAME
    new GameOverRoom(), // RoomID::GAME_OVER
};

SpaceShooterGame::SpaceShooterGame()
{

}

SpaceShooterGame::~SpaceShooterGame()
{
    if (m_standardFont)
    {
        TTF_CloseFont(m_standardFont);
    }
}

Room* SpaceShooterGame::GameStartRoom() const
{
    std::cout << "TESTLEVEL LOADED" << std::endl;
    return new TestLevel();
}

//void SpaceShooterGame::ExecuteUpdate(float deltaTime)
//{
//
//}
//
//void SpaceShooterGame::ExecuteDrawUpdate(SDL_Renderer* renderer)
//{
//
//}

void SpaceShooterGame::InitializeGame()
{
    this->GameBase::InitializeGame();

    m_standardFont = TTF_OpenFont("Resources/default_font.ttf", 20);
    if (!m_standardFont)
    {
        printf("%s\n", TTF_GetError());
        std::cout << "Loading font failed." << std::endl;
    }
}

void SpaceShooterGame::Subscribe_OnNewScoreSet(OnNewScoreSet* newScore)
{
    m_onNewScoreSet.Subscribe(newScore);
}

void SpaceShooterGame::Unsubscribe_OnNewScoreSet(OnNewScoreSet* newScore)
{
    m_onNewScoreSet.Unsubscribe(newScore);
}

void SpaceShooterGame::SetStandardFont(TTF_Font* newFont)
{
    if (m_standardFont)
    {
        TTF_CloseFont(m_standardFont);
    }

    m_standardFont = newFont;
}

void SpaceShooterGame::GoToRoomByID(const RoomID roomID, bool rememberPreviousRoom)
{
    int intID = static_cast<int>(roomID);
    GoToRoom(m_gameRooms[intID], rememberPreviousRoom);
}
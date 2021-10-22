#include "GameOverScreen.h"

#include "Statics.h"
#include "SpaceShooterGame.h"
#include "InputGet.h"

GameOver::GameOver(const Vector2 position, float rotation, bool enabled) : GameObject(position, rotation, enabled)
{

}

GameOver::~GameOver()
{

}

void GameOver::OnEstablished()
{
	SpaceShooterGame* game = (SpaceShooterGame*)Statics::GetGameBase();

	TTF_Font* font;
	if (game)
	{
		font = game->GetStandardFont();
	}
	else
	{
		font = nullptr;
	}

	m_gameOverText = new TextObject({ 400, 300 }, 0, true, "GAME OVER", font);
	m_retryText = new TextObject({ 400, 332 }, 0, true, "Press Space to Retry", font);
}

void GameOver::Update(float deltaTime)
{
	if (Input_GetKeyDown(SDLK_SPACE))
	{
		SpaceShooterGame* game = (SpaceShooterGame*)Statics::GetGameBase();
		if (game)
		{
			game->GoToRoomByID(RoomID::MAIN_GAME, false);
		}
	}
}

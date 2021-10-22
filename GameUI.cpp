#include "GameUI.h"
#include "Statics.h"
#include "InputGet.h"

//#include "SpaceShip.h"

GameUI::GameUI(const Vector2 position, float rotation, bool enabled, PlayerObject* targetObject) : GameObject(position, rotation, enabled)
{
	SetPlayerObject(targetObject);

}

void GameUI::OnEstablished()
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

	std::string livesLabelText = "LIVES: ";
	std::string scoreLabelText = "SCORE: ";

	std::string lives;
	//if (std::shared_ptr<IPlayerObject> spt = m_playerObject.lock())
	if (m_playerObject)
	{
		Uint8 num = m_playerObject->GetLives();
		lives = std::to_string(num);
	}
	else
	{
		lives = "0";
	}

	m_livesLabel = new TextObject(m_livesPosition, 0, true, livesLabelText, font);
	m_livesCount = new TextObject(m_livesPosition + Vector2(96, 0), 0, true, lives, font);

	m_livesLabel->SetText(livesLabelText, font);
	m_livesCount->SetText(lives, font);

	std::string score;
	if (game)
	{
		score = std::to_string(game->GetScore());
	}
	else
	{
		score = "0";
	}

	m_scoreLabel = new TextObject(m_scorePosition, 0, true, scoreLabelText, font);
	m_scoreCount = new TextObject(m_scorePosition + Vector2(96, 0), 0, true, score, font);

	m_scoreLabel->SetText(scoreLabelText, font);
	m_scoreCount->SetText(score, font);
}

GameUI::~GameUI()
{
	SetPlayerObject(nullptr);

	if (m_livesCount)
		m_livesCount->Destroy();

	if (m_livesLabel)
		m_livesLabel->Destroy();

	if (m_scoreCount)
		m_scoreCount->Destroy();

	if (m_scoreLabel)
		m_scoreLabel->Destroy();
}

void GameUI::OnPlayerObjectDestroyed(PlayerObject* playerObject)
{
	if (playerObject == m_playerObject)
	{
		SetPlayerObject(nullptr);
	}
}

void GameUI::OnLivesChanged(Uint8 newLives)
{
	SpaceShooterGame* game = (SpaceShooterGame*)Statics::GetGameBase();
	if (game)
	{
		m_livesCount->SetText(std::to_string(newLives), game->GetStandardFont());
	}
}

void GameUI::OnScoreChanged(Uint32 newScore)
{
	SpaceShooterGame* game = (SpaceShooterGame*)Statics::GetGameBase();
	if (game)
	{
		m_livesCount->SetText(std::to_string(game->GetScore()), game->GetStandardFont());
	}
}

void GameUI::Update(float deltaTime)
{
}

void GameUI::GetTextObjects(TextObject*& livesLabel, TextObject*& livesCount, TextObject*& scoreLabel, TextObject*& scoreCount) const
{
	livesLabel = m_livesLabel;
	livesCount = m_livesCount;
	scoreLabel = m_scoreLabel;
	scoreCount = m_scoreCount;
}

void GameUI::SetPlayerObject(PlayerObject* newPlayerObject)
{
	//if (std::shared_ptr<IPlayerObject> spt = m_playerObject.lock())
	if (m_playerObject)
	{
 		m_playerObject->Unsubscribe_OnLivesChange(&m_onLivesChangedEventWrapper);

		m_playerObject->Unsubscribe_OnPlayerObjectDestroyed(&m_playerObjectDestroyedEventWrapper);
	}

	m_playerObject = newPlayerObject;//std::make_shared<IPlayerObject>(newPlayerObject);

	//if (std::shared_ptr<IPlayerObject> spt = m_playerObject.lock())
	if (m_playerObject)
	{
		m_playerObject->Subscribe_OnPlayerObjectDestroyed(&m_playerObjectDestroyedEventWrapper);
		m_playerObject->Subscribe_OnLivesChange(&m_onLivesChangedEventWrapper);
	}
}

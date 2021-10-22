#pragma once

#include "GameObject.h"
#include "TextObject.h"
#include "PlayerObject.h"
#include "SpaceShooterGame.h"

class GameUI : public GameObject
{
public:
	GameUI(const Vector2 position, float rotation = 0, bool enabled = true, PlayerObject* targetObject = nullptr);
	~GameUI();

	virtual void OnEstablished() override;

private:
	// Lives
	Vector2 m_livesPosition = Vector2(96, 32);
	TextObject* m_livesLabel = nullptr;
	TextObject* m_livesCount = nullptr;

	// Score
	Vector2 m_scorePosition = Vector2(480, 32);
	TextObject* m_scoreLabel = nullptr;
	TextObject* m_scoreCount = nullptr;

	//std::weak_ptr<IPlayerObject> m_playerObject = std::weak_ptr<IPlayerObject>();

	// The player object the UI keeps track of.
	// NOTE: Do NOT delete this manually!!! 
	// Use SetPlayerObject() instead!
	PlayerObject* m_playerObject = nullptr;

protected:
	void OnPlayerObjectDestroyed(PlayerObject* playerObject);

	/*virtual */void OnLivesChanged(Uint8 newLives);

	/*virtual */void OnScoreChanged(Uint32 newScore);

	virtual void Update(float deltaTime) override;

public:
	virtual std::string GetGameObjectName() override { return "GameUI"; }

	virtual GameObjectID GetID() const override { return GameObjectID::GAME_UI; }

	/*virtual int GetMaxExistingObjects() const override { return 1; }*/

	void GetTextObjects(TextObject*& livesLabel, TextObject*& livesCount, TextObject*& scoreLabel, TextObject*& scoreCount) const;

public:
	void SetPlayerObject(PlayerObject* newPlayerObject);

public:
	PlayerObject::OnLivesChange m_onLivesChangedEventWrapper = [this](Uint8 newLives) { OnLivesChanged(newLives); };
	SpaceShooterGame::OnNewScoreSet m_onNewScoreSetWrapper = [this](Uint32 newScore) { OnScoreChanged(newScore); };
	PlayerObject::OnPlayerObjectEvent m_playerObjectDestroyedEventWrapper = [this](PlayerObject* playerObject) { OnPlayerObjectDestroyed(playerObject); };
};


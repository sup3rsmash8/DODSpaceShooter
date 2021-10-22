#pragma once

#include "TextObject.h"



class GameOver : public GameObject
{
public:
	GameOver(const Vector2 position, float rotation = 0, bool enabled = true);
	~GameOver();

	virtual void OnEstablished() override;

private:
	TextObject* m_gameOverText = nullptr;
	TextObject* m_retryText = nullptr;

protected:
	virtual void Update(float deltaTime) override;

public:
	virtual GameObjectID GetID() const override { return GameObjectID::GAME_OVER; }
};


#pragma once

#include "SDL.h"
#include "GameObject.h"

#include <functional>

class PlayerObject : public GameObject
{


public:
	typedef std::function<void(PlayerObject*)> OnPlayerObjectEvent;
	typedef std::function<void(Uint8)> OnLivesChange;

	PlayerObject();
	PlayerObject(const Vector2 position, float rotation = 0, bool enabled = true, Uint8 lives = 3);
	virtual ~PlayerObject();

private:
	MulticastFunction<PlayerObject*> m_onPlayerObjectDestroyed = MulticastFunction<PlayerObject*>();
	MulticastFunction<Uint8> m_onLivesChanged = MulticastFunction<Uint8>();

protected:
	Uint8 m_lives = 3;

public:
	virtual Uint8 GetLives() const { return m_lives; }

	virtual void SetLives(Uint8 newLifeCount) 
	{ 
		m_lives = newLifeCount; 
		m_onLivesChanged.Call(std::tuple<Uint8>(m_lives));
	}

	void Subscribe_OnLivesChange(OnLivesChange* livesLostDelegate) { m_onLivesChanged.Subscribe(livesLostDelegate); }
	void Unsubscribe_OnLivesChange(OnLivesChange* livesLostDelegate) { m_onLivesChanged.Unsubscribe(livesLostDelegate); }

	virtual void Subscribe_OnPlayerObjectDestroyed(OnPlayerObjectEvent* playerObjectEvent) { m_onPlayerObjectDestroyed.Subscribe(playerObjectEvent); }
	virtual void Unsubscribe_OnPlayerObjectDestroyed(OnPlayerObjectEvent* playerObjectEvent) { m_onPlayerObjectDestroyed.Unsubscribe(playerObjectEvent); }
};


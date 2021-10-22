#include "PlayerObject.h"

PlayerObject::PlayerObject()
{
	m_lives = 3;
	SetPosition(VEC2_ZERO);
	SetRotation(0);
	SetEnabled(true);
}

PlayerObject::PlayerObject(const Vector2 position, float rotation, bool enabled, Uint8 lives) : GameObject(position, rotation, enabled)
{
	m_lives = lives;
}

PlayerObject::~PlayerObject()
{
	m_onPlayerObjectDestroyed.Call(std::tuple<PlayerObject*>(this));
}

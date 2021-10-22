#include "SpaceShooterGameObject.h"

SpaceShooterGameObject::SpaceShooterGameObject()
{
	SetPosition(VEC2_ZERO);
	SetRotation(0);
	SetEnabled(true);
}

SpaceShooterGameObject::SpaceShooterGameObject(const Vector2 position, float rotation, bool enabled) : GameObject(position, rotation, enabled)
{
	SetPosition(position);
	SetRotation(rotation);
	SetEnabled(enabled);
}

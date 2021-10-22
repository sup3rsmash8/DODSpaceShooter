#pragma once

#include "GameObject.h"


class SpaceShooterGameObject : public GameObject
{
public:
	SpaceShooterGameObject();
	SpaceShooterGameObject(const Vector2 position, float rotation = 0, bool enabled = true);


};


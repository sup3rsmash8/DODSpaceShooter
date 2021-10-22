#pragma once

#include "Projectile.h"
#include "Collider.h"

class EnemyProjectile : public Projectile
{
public:
	EnemyProjectile();
	EnemyProjectile(const Vector2 position, float rotation = 0, bool enabled = true);//

	virtual void OnEstablished() override;

private:
	static const char* m_projectileTexturePath;

	static SDL_Texture* m_projectileTexture;

	static const float m_moveSpeed;

	static const float m_lifetime;
	/*virtual void OnEnabled() override;*/

	//virtual void OnDisabled() override;

protected:
	virtual void OnCollision(GameObject* other) override;

public:
	virtual GameObjectID GetID() const override { return GameObjectID::ENEMY_PROJECTILE; }

	virtual float GetProjectileSpeed() const { return m_moveSpeed; }
	virtual float GetProjectileLifetime() const { return m_lifetime; }
	/*virtual int GetMaxExistingObjects() const override { return 50; }*/
};


#include "Projectile.h"

#include "Library.h"
#include <iostream>

Projectile::Projectile()
{
}

Projectile::Projectile(const Vector2 position, float rotation, bool enabled) : GameObject(position, rotation, enabled)
{
	
}

void Projectile::OnEstablished()
{
	m_collider = new Collider(this, 16.f, &m_onCollisionEvent);
}

Projectile::~Projectile()
{
	delete m_collider;
}

void Projectile::OnCollision(GameObject* other)
{
	if (other && (other->GetID() == GameObjectID::ASTEROID ||
		other->GetID() == GameObjectID::ENEMY_SHIP))
	{
		DestroyProjectile();
	}
}

void Projectile::Update(float deltaTime)
{
	m_existenceTimer -= deltaTime;
	if (m_existenceTimer <= 0.f)
	{
		DestroyProjectile();
	}
}

//void PlayerProjectile::OnEnabled()
//{
//	m_existenceTimer = m_lifetime;
//	SetSpeed(Vector2::GetForward(GetRotation()) * m_moveSpeed);
//}

//void PlayerProjectile::OnDisabled()
//{
//}

void Projectile::Shoot(const Vector2 position, float rotation)
{
	SetPosition(position);
	SetRotation(rotation);
	SetSpeed(Vector2::GetForward(GetRotation() + 90.f) * GetProjectileSpeed());
	m_existenceTimer = GetProjectileLifetime();
	SetEnabled(true);
}

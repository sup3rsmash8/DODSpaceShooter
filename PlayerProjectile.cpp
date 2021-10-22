
#include "PlayerProjectile.h"
#include "Library.h"
#include <iostream>

const char* PlayerProjectile::m_projectileTexturePath = "Resources/laserBullet.png";
//const float PlayerProjectile::m_maxExistingObjects = 50;
//std::shared_ptr<SDL_Texture> PlayerProjectile::m_projectileTexture = nullptr;
SDL_Texture* PlayerProjectile::m_projectileTexture = nullptr;

const float PlayerProjectile::m_moveSpeed = 600.f;

const float PlayerProjectile::m_lifetime = 3.f;

PlayerProjectile::PlayerProjectile()
{
	//SetTextureFromFile(m_projectileTexturePath, m_projectileTexture);

	//int w, h;

	//if (SDL_QueryTexture(m_projectileTexture.get(), NULL, NULL, &w, &h) == 0)
	//{
	//	std::cout << SDL_GetError() << std::endl;
	//}

	//m_texture = GameTexture(m_projectileTexture, Vector2(static_cast<float>(w), static_cast<float>(h)) * 0.5f, Vector2(0.5f, 0.5f));
}

PlayerProjectile::PlayerProjectile(const Vector2 position, float rotation, bool enabled) : Projectile(position, rotation, enabled)
{

}

void PlayerProjectile::OnEstablished()
{
	this->Projectile::OnEstablished();

	SetTextureFromFile(m_projectileTexturePath, m_projectileTexture);

	int w, h;

	if (SDL_QueryTexture(m_projectileTexture/*.get()*/, NULL, NULL, &w, &h) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
	}

	m_texture = GameTexture(m_projectileTexture, Vector2(static_cast<float>(w), static_cast<float>(h)) * 0.5f, Vector2(0.5f, 0.5f));

	//m_collider = new Collider(this, 16.f, &m_onCollisionEvent);
}

void PlayerProjectile::OnCollision(GameObject* other)
{
	if (other && (other->GetID() == GameObjectID::ASTEROID ||
		other->GetID() == GameObjectID::ENEMY_SHIP))
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
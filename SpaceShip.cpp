#include "SpaceShip.h"
#include "Statics.h"
#include "SDL_image.h"
#include "InputGet.h"
#include "VectorExtensions.h"
#include "Particle_ShipExplosion.h"
#include "RoomID.h"
#include "SpaceShooterGame.h"

#include <algorithm>
#include <SDL_ttf.h>

const char* SpaceShip::m_standardTexturePath = "Resources/Ship.png";

SDL_Texture* SpaceShip::m_standardTexture = nullptr;
//std::shared_ptr<SDL_Texture> SpaceShip::m_standardTexture = nullptr;

SpaceShip::SpaceShip(const Vector2 position, float rotation, bool enabled) : PlayerObject(position, rotation, enabled)
{

}

SpaceShip::~SpaceShip()
{
	delete m_collider;

	if (m_part_shipExplosion)
		m_part_shipExplosion->Destroy();
}

void SpaceShip::OnEstablished()
{
	SetTextureFromFile(m_standardTexturePath, m_standardTexture);

	int w, h;

	if (SDL_QueryTexture(m_standardTexture/*.get()*/, NULL, NULL, &w, &h) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
	}

	m_texture = GameTexture(m_standardTexture, Vector2(static_cast<float>(w), static_cast<float>(h)), Vector2(0.5f, 0.5f));

	SetRotation(90);

	m_collider = new Collider(this, 16.f, &m_onCollisionEvent);


	if (!m_part_shipExplosion)
	{
		m_part_shipExplosion = new Particle_ShipExplosion();
	}
	//SDL_DestroyTexture
}

void SpaceShip::Update(float deltaTime)
{
	Movement(deltaTime);

	if (m_shootTimer <= 0)
	{
		if (Input_GetKey(SDLK_SPACE))
		{
			m_shootTimer = m_shootIntervalTime;

			PlayerProjectile* projectile = m_projectilePool.GetPooledObject();
			if (projectile)
			{
				projectile->Shoot(GetPosition(), GetRotation());
			}
			else
			{
				printf("Projectile was null, so it couldn't be spawned. :(\n");
			}
		}
	}
	else
	{
		m_shootTimer -= deltaTime;
	}

	if (m_respawnTimer > 0)
	{
		m_respawnTimer -= deltaTime;
		
		// Flicker during respawn
		if (m_respawnTimer < 0)
		{
			SetRender(true);
		}
		else
		{
			SetRender(!GetRender());
		}
	}
}

void SpaceShip::DrawUpdate(SDL_Renderer* renderer)
{
	if (!m_texture.texture)
	{
		printf("Texture could not be rendered: %s\n", SDL_GetError());
	}
}

void SpaceShip::OnCollision(GameObject* other)
{
	if (!other)
		return;

	if (m_respawnTimer <= 0)
	{
		const GameObjectID otherID = other->GetID();
		if (otherID == GameObjectID::ASTEROID || 
			otherID == GameObjectID::ENEMY_PROJECTILE ||
			otherID == GameObjectID::ENEMY_SHIP)
		{
			if (m_part_shipExplosion)
			{
				m_part_shipExplosion->SetPosition(GetPosition());
				m_part_shipExplosion->Play();
			}

			SetRespawnTimer();

			SetLives(GetLives() - 1);

			if (GetLives() <= 0)
			{
				SpaceShooterGame* game = (SpaceShooterGame*)Statics::GetGameBase();

				game->GoToRoomByID(RoomID::GAME_OVER, false);
			}

			SetPosition({ 128, 300 });
		}
	}
}

void SpaceShip::Movement(float deltaTime)
{
	const float speed = m_moveSpeed * deltaTime;

	if (Input_GetKey(SDLK_UP))
	{
		SetPosition(GetPosition() + Vector2(0, -1) * speed);
	}
	else if (Input_GetKey(SDLK_DOWN))
	{
		SetPosition(GetPosition() + Vector2(0, 1) * speed);
	}

	if (Input_GetKey(SDLK_LEFT))
	{
		SetPosition(GetPosition() + Vector2(-1, 0) * speed);
	}
	else if (Input_GetKey(SDLK_RIGHT))
	{
		SetPosition(GetPosition() + Vector2(1, 0) * speed);
	}

	SDL_Rect roomRect = Statics::GetRoomView();
	Vector2 clampedPosition = GetPosition();

	if (clampedPosition.x < roomRect.x)
		clampedPosition.x = 0;
	else if (clampedPosition.x > roomRect.x + roomRect.w)
		clampedPosition.x = static_cast<float>(roomRect.x + roomRect.w);

	if (clampedPosition.y < roomRect.y)
		clampedPosition.y = 0;
	else if (clampedPosition.y > roomRect.y + roomRect.h)
		clampedPosition.y = static_cast<float>(roomRect.y + roomRect.h);

	SetPosition(clampedPosition);
	//SDL_Rect roomView;
}

//Uint8 SpaceShip::GetLives() const
//{
//	return m_lives;
//}
//
//void SpaceShip::SetLives(const Uint8 newLifeCount)
//{
//	m_lives = newLifeCount;
//
//	m_onLivesChanged.Call(std::tuple<Uint8>(newLifeCount));
//};

//void SpaceShip::Subscribe_OnLivesChange(OnLivesChange* livesLostDelegate)
//{
//	m_onLivesChanged.Subscribe(livesLostDelegate);
//}
//
//void SpaceShip::Unsubscribe_OnLivesChange(OnLivesChange* livesLostDelegate)
//{
//	m_onLivesChanged.Unsubscribe(livesLostDelegate);
//}
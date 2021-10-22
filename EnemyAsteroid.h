#pragma once

#include "Collider.h"
#include "GameObject.h"
#include "Particle_AsteroidExplosion.h"

class EnemyAsteroid : public GameObject
{
public:
	EnemyAsteroid();
	EnemyAsteroid(const Vector2 position, float rotation = 0, bool enabled = true);
	~EnemyAsteroid();

	virtual void OnEstablished() override;

private:
	static const char* m_asteroidTexturePath;

	//static std::shared_ptr<SDL_Texture> m_asteroidTexture;
	static SDL_Texture* m_asteroidTexture;

	// After this many seconds of spawning (be it by creation or enabled)
	// the asteroid will be disabled.
	const float m_lifetime = 10.f;

	// The variable that counts up to m_lifetime.
	float m_lifetimer = 0.f;

	// Pixels/s
	float m_mySpeed = 100.f;

	// Deg/s
	float m_rotationSpeed = 480.f;	

	ParticleSystem* m_part_asteroidExplosion = nullptr;
	
	Collider* m_collider = nullptr;

	void OnCollision(GameObject* other);

	Collider::OnCollisionEvent m_onCollisionEvent = [this](GameObject* other) { OnCollision(other); };

	void Initialize();

public:
	virtual GameObjectID GetID() const override { return GameObjectID::ASTEROID; }

	/*virtual int GetMaxExistingObjects() const override { return 50; }*/

	virtual void Update(float deltaTime) override;

	virtual void DrawUpdate(SDL_Renderer* renderer) override;

	virtual void OnEnabled() override;


};


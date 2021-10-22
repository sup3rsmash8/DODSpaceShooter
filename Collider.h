#pragma once
#include <functional>
#include <vector>
#include <memory>
#include "SDL_thread.h"
#include "Collider.h"

class GameObject;

class Collider
{
	friend class GameEngine;

public:
	typedef std::function<void(GameObject*)> OnCollisionEvent;

	Collider(GameObject* owner, float radius, OnCollisionEvent* onCollision);
	~Collider();

private:
	float m_radius = 32.f;

	// Lifetime of a collider is expected to be exactly 
	// that of the GameObject it is attached to.
	GameObject* m_owner = nullptr;

	OnCollisionEvent* m_onCollisionEvent = nullptr;

	static std::vector<Collider*> m_allColliders;

	static SDL_mutex* m_collisionUpdateMutex;

	// Multithread operation that calculates collision 
	// between all active colliders in the room.
	// void* = std::map<Collider*, Collider*>
	static int Thread_CollisionUpdate(void* outStdMapCollision);

	void OnCollision(GameObject* other);

public:
	float GetRadius() const { return m_radius; }
	void SetRadius(float newRadius) { m_radius = newRadius; }
};


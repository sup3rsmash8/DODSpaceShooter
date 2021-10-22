#include "Collider.h"
#include "GameObject.h"
#include "VectorExtensions.h"

std::vector<Collider*> Collider::m_allColliders = std::vector<Collider*>();

SDL_mutex* Collider::m_collisionUpdateMutex = SDL_CreateMutex();

Collider::Collider(GameObject* owner, float radius, OnCollisionEvent* onCollision)
{
	m_owner = owner;
	
	m_onCollisionEvent = onCollision;

	SetRadius(radius);

	m_allColliders.push_back(this);
}

Collider::~Collider()
{
	//m_onCollisionEvent = nullptr;
	EraseObjectFromVector<Collider*>(m_allColliders, this);
}

int Collider::Thread_CollisionUpdate(void* outStdMapCollision)
{
	std::map<Collider*, Collider*>* collided = (std::map<Collider*, Collider*>*)outStdMapCollision;

	if (!collided)
		return 0;

	if (SDL_LockMutex(m_collisionUpdateMutex) == 0)
	{
		for (Collider* collider1 : m_allColliders)
		{
			if (!collider1)
				continue;

			for (Collider* collider2 : m_allColliders)
			{
				if (MapContainsAsKeyOrValue(*collided, collider1, collider2))
					continue;

				if (collider2 && collider2 != collider1)
				{
					GameObject* user1 = collider1->m_owner;
					GameObject* user2 = collider2->m_owner;
					if (user1 && user1->IsEnabled() && !user1->IsMarkedForDestruction() 
						&& user2 && user2->IsEnabled() && !user2->IsMarkedForDestruction())
					{
						const float dist = (user1->GetPosition() - user2->GetPosition()).sqrMagnitude();

						if (dist < collider1->GetRadius() * collider1->GetRadius())
						{
							collided->emplace(collider1, collider2);
							//collider1->OnCollision(collider2);
							//collider2->OnCollision(collider1);
						}
					}
				}
			}
		}

		SDL_UnlockMutex(m_collisionUpdateMutex);
	}

	return 0;
}

void Collider::OnCollision(GameObject* other)
{
	if (m_onCollisionEvent)
	{
		(*m_onCollisionEvent)(other);
	}
}

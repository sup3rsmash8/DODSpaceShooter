#pragma once

#include "GameObject.h"
#include <vector>
#include "VectorExtensions.h"
//#include "TupleUnpackers.h"

template<class T>
struct ObjectPool
{
	//static_assert(std::is_base_of<GameObject, T>::value, "ObjectPool may only be used with type GameObject!");
	//static_assert(std::is_default_constructible_v<T>,
	//	"Object must have a default constructor.");
public:
	ObjectPool();
	~ObjectPool();

private:
	std::vector<T*> m_pooledObjects = std::vector<T*>();

	std::function<void(GameObject*, GameObjectEventType)> m_gameObjectEvent = 
		[this](GameObject* gameObject, GameObjectEventType eventType) { OnGameObjectEvent(gameObject, eventType);  };

	void OnGameObjectEvent(GameObject* gameObject, GameObjectEventType eventType);

public:
	// Returns a disabled GameObject of templated type. If no object exists or is currently disabled,
	// 
	T* GetPooledObject();
};

template<class T>
inline ObjectPool<T>::ObjectPool()
{
	GameObject::SubscribeGameObjectEvent(&m_gameObjectEvent);
}

template<class T>
inline ObjectPool<T>::~ObjectPool()
{
	GameObject::UnsubscribeGameObjectEvent(&m_gameObjectEvent);
}

template<class T>
inline T* ObjectPool<T>::GetPooledObject()
{
	for (T* obj : m_pooledObjects)
	{
		// Just to make sure
		if (obj && !obj->IsEnabled())
		{
			return obj;
		}
	}

	return new T();
}

template<class T>
inline void ObjectPool<T>::OnGameObjectEvent(GameObject* gameObject, GameObjectEventType eventType)
{
	T* eventObject = dynamic_cast<T*>(gameObject);

	if (!eventObject)
	{
		return;
	}

	switch (eventType)
	{
	case GameObjectEventType::DISABLED:
		m_pooledObjects.push_back(eventObject);
		break;

	case GameObjectEventType::DESTROYED:
	case GameObjectEventType::ENABLED:
		EraseObjectFromVector(m_pooledObjects, eventObject);
		break;
	}
}

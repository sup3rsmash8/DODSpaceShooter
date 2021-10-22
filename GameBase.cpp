#include "GameBase.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "VectorExtensions.h"
#include "Statics.h"

//#include "SpaceShip.h"

#include <iostream>

GameBase::GameBase()
{
}

GameBase::~GameBase()
{
	// This will most likely cause random crashes due to 
	// the collision thread if deleted during update time. 
	// Improve this shit

	m_trashCan.clear();

	for (auto& pair : m_existingObjectMaps)
	{
		for (size_t i = 0, ilen = pair.second.size(); i < ilen; ++i)
		{
			if (i >= pair.second.size())
				break;

			m_trashCan.push_back(pair.second[i]);
		}
	}

	EmptyTrashCan();

	if (m_currentRoom)
	{
		delete m_currentRoom;
		m_currentRoom = nullptr;
	}
}

void GameBase::ExecuteUpdate(float deltaTime)
{
	//this->GameBase::ExecuteUpdate(deltaTime);

	if (deltaTime > GetMaxTimeStep())
		deltaTime = GetMaxTimeStep();

	for (auto& pair : m_existingObjectMaps)
	{
		for (size_t i = 0, ilen = pair.second.size(); i < ilen; ++i)
		{
			if (i >= pair.second.size())
				break;

			// I should've maybe had a separate array of enabled
			// objects to avoid unnecessary iterations :|
			if (pair.second[i] && pair.second[i]->IsEnabled())
				ExecuteObject(pair.second[i], deltaTime);
		}
	}
}

void GameBase::PostExecuteUpdate()
{
	EstablishNewObjects();
	// Delete objects marked for destruction 
	// and remove them from relevant vectors
	EmptyTrashCan();

	if (m_buffer_room)
	{
		Exec_GoToRoom(m_buffer_room, m_buffer_rememberPreviousRoom);
		m_buffer_room = nullptr;
	}
}

void GameBase::ExecuteDrawUpdate(SDL_Renderer* renderer)
{
	for (auto& pair : m_existingObjectMaps)
	{
		for (size_t i = 0, ilen = pair.second.size(); i < ilen; ++i)
		{
			if (i >= pair.second.size())
				break;

			if (pair.second[i] && pair.second[i]->IsEnabled())
				ExecuteDrawObject(pair.second[i], renderer);
		}
	}
}

void GameBase::ExecuteObject(GameObject* gameObject, float deltaTime)
{
	if (gameObject)
	{
		gameObject->Exec_Update(deltaTime);

		// Throw in trash bin
		if (gameObject->IsMarkedForDestruction())
		{
			m_trashCan.push_back(gameObject);
		}
	}
}

void GameBase::ExecuteDrawObject(GameObject* gameObject, SDL_Renderer* renderer)
{
	if (gameObject)
		gameObject->Exec_DrawUpdate(renderer);
}

void GameBase::EstablishNewObjects()
{
	if (!m_pendingNewObjects.empty())
	{
		size_t pendingObjSize = m_pendingNewObjects.size();
		for (size_t i = 0; i < pendingObjSize; i++)
		{
			_ObjectListAction_NewObject(m_pendingNewObjects[i]);

			pendingObjSize = m_pendingNewObjects.size();
		}

		m_pendingNewObjects.clear();
	}
}

void GameBase::OnGameReset()
{
	OnGameStart();
}

float GameBase::Time() const
{
	return Statics::GetGameEngine()->Time();
}

float GameBase::DeltaTime() const
{
	return Statics::GetGameEngine()->DeltaTime();
}

GameBase* GameBase::GetEngineGameBase() const
{
	return Statics::GetGameEngine()->GetGameBase();
}

Room* GameBase::GetRoom() const
{
	return m_currentRoom;
}

void GameBase::GoToRoom(Room* room, bool rememberPreviousRoom)
{
	m_buffer_room = room;
	m_buffer_rememberPreviousRoom = rememberPreviousRoom;
}

void GameBase::Exec_GoToRoom(Room* room, bool rememberPreviousRoom)
{
	if ((room == m_currentRoom && rememberPreviousRoom))
	{
		return;
	}

	if (m_currentRoom)
	{
		if (rememberPreviousRoom)
		{
			// Store all current objects in memory
			m_currentRoom->m_existingObjectMapCache = m_existingObjectMaps;
		}
		else
		{
			// Clear cache of anything danglable before destroying our objects
			m_currentRoom->m_existingObjectMapCache.clear();

			// Now clear the room contents from memory

			// Reset the trash can to refill it fresh
			// (we don't want duplicate pointers to exist in the bin)
			m_trashCan.clear();

			for (auto& pair : m_existingObjectMaps)
			{
				for (size_t i = 0, ilen = pair.second.size(); i < ilen; ++i)
				{
					if (i >= pair.second.size())
						break;

					m_trashCan.push_back(pair.second[i]);
				}
			}
		}

		m_currentRoom->m_isRemembered = rememberPreviousRoom;
	}

	// Now we can empty
	EmptyTrashCan();

	m_existingObjectMaps.clear();

	m_currentRoom = room;

	if (m_currentRoom)
	{
		// Shit programming move, but...

		// If unloaded, the Room will load the objects into its cache 
		// according to its LoadRoomObjects() function.
		m_currentRoom->OnRoomLoad();

		
		// Its cache is always considered, regardless of whether it was
		// remembered or not.
		m_existingObjectMaps = m_currentRoom->m_existingObjectMapCache;
	}
}

GameObject* GameBase::GetExistingGameObjectByID(const GameObjectID gameObjectID, const int index) const
{
	if (m_existingObjectMaps.find(gameObjectID) == m_existingObjectMaps.end())
		return nullptr;

	if (m_existingObjectMaps.at(gameObjectID).empty())
		return nullptr;

	return m_existingObjectMaps.at(gameObjectID)[index];
}

int GameBase::GetGameObjectCount(const GameObjectID gameObjectID) const
{
	if (m_existingObjectMaps.find(gameObjectID) == m_existingObjectMaps.end())
		return 0;

	return m_existingObjectMaps.at(gameObjectID).size();
}

bool GameBase::GetAllGameObjectsByID(std::vector<GameObject*>& vector, const GameObjectID gameObjectID) const
{
	if (!(m_existingObjectMaps.find(gameObjectID) == m_existingObjectMaps.end() || 
		m_existingObjectMaps.at(gameObjectID).empty()))
	{
		vector = m_existingObjectMaps.at(gameObjectID);

		return true;
	}

	return false;
}

//GameObject* GameBase::GetExistingGameObject(int index) const
//{
//	if (index >= m_existingGameObjects.size())
//		return nullptr;
//
//	return m_existingGameObjects[index];
//}
//
//GameObject* GameBase::GetEnabledGameObject(int index) const
//{
//	if (index >= m_enabledGameObjects.size())
//		return nullptr;
//
//	return m_enabledGameObjects[index];
//}

void GameBase::OnGameObjectEvent(GameObject* gameObject, GameObjectEventType eventType)
{
	switch (eventType)
	{
	case GameObjectEventType::CREATED:
		m_pendingNewObjects.push_back(gameObject);
		break;

	case GameObjectEventType::ENABLED:
		_ObjectListAction_EnabledObject(gameObject);
		break;

	case GameObjectEventType::DISABLED:
		_ObjectListAction_DisabledObject(gameObject);
		break;

	//case GameObjectEventType::DESTROYED:
	//	EraseObjectFromVector<GameObject>(m_enabledGameObjects, gameObject);
	//	EraseObjectFromVector<GameObject>(m_existingGameObjects, gameObject);
	//	break;
	}
}

void GameBase::EmptyTrashCan()
{
	if (m_trashCan.size() > 0)
	{
		for (size_t i = 0, ilen = m_trashCan.size(); i < ilen; ++i)
		{
			if (m_trashCan[i])
			{
				_ObjectListAction_DestroyedObject(m_trashCan[i]);
			}
		}

		m_trashCan.clear();
	}
}

void GameBase::InitializeGame()
{
	GameObject::SubscribeGameObjectEvent(&onGameObjectEventWrapper);
}

void GameBase::LateInitializeGame()
{
	GoToRoom(GameStartRoom(), false);
}

void GameBase::UninitializeGame()
{
	GameObject::UnsubscribeGameObjectEvent(&onGameObjectEventWrapper);
}

void GameBase::_ObjectListAction_NewObject(GameObject* gameObject)
{	
	if (!gameObject)
	{
		return;
	}

	GameObjectID id = gameObject->GetID();

	// If id is non-existent in map, add.
	if (m_existingObjectMaps.find(id) == m_existingObjectMaps.end())
	{
		std::vector<GameObject*> mapVector = std::vector<GameObject*>();
		mapVector.push_back(gameObject);

		m_existingObjectMaps.emplace(id, mapVector);
	}
	else
	{
		// If it exists, push it into the correct map ID.
		if (!VectorContains(m_existingObjectMaps[id], gameObject))
			m_existingObjectMaps[id].push_back(gameObject);
	}

	gameObject->OnEstablished();
	//m_existingGameObjects.push_back(gameObject);
	//if (gameObject->IsEnabled() && !VectorContains(m_enabledGameObjects, gameObject))
	//{
	//    m_enabledGameObjects.push_back(gameObject);
	//}
}

void GameBase::_ObjectListAction_DestroyedObject(GameObject* gameObject)
{
	//if (gameObject)
	//{
	//	GameObjectID id = gameObject->GetID();
	//	EraseObjectFromVector(m_existingObjectMaps[id], gameObject);
	//}

	GameObjectID id = gameObject->GetID();
	EraseObjectFromVector(m_existingObjectMaps[id], gameObject);

	delete gameObject;
}

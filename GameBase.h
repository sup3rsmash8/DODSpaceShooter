#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "Pair.h"
#include "Library.h"
#include "Room.h"
#include "SDL_image.h"

class GameObject;
enum class GameObjectEventType;

/// <summary>
/// Base class for the entire game itself.
/// </summary>
class GameBase
{
	friend class GameEngine;

public:
	GameBase();
	virtual ~GameBase();

private:
	// Default values //
	const std::string m_defaultBaseGameName = "Base_Game";
	const Vector2 m_defaultScreenResolution = Vector2(800.f, 600.f);
	const float m_defaultTimeStep = 0.0166667f;
	const float m_defaultDrawTimeStep = 0.0166667f;
	const float m_defaultMaxTimeStep = .5f;

	Room* m_currentRoom = nullptr;

	// Room changes are buffered here, when called in an Update function.
	Room* m_buffer_room = nullptr;
	bool m_buffer_rememberPreviousRoom = false;

protected:
	// This system will always organize objects by their IDs.
	// The update in order of keys.
	std::map<GameObjectID, std::vector<GameObject*>> m_existingObjectMaps = std::map<GameObjectID, std::vector<GameObject*>>();

	std::vector<GameObject*> m_pendingNewObjects = std::vector<GameObject*>();

	std::vector<GameObject*> m_trashCan = std::vector<GameObject*>();

	void ExecuteUpdate(float deltaTime);

	void ExecuteDrawUpdate(SDL_Renderer* renderer);

	// This is where new objects are spawned and
	// objects marked for destruction are deleted.
	void PostExecuteUpdate();

	// Calls update on an object.
	void ExecuteObject(GameObject* gameObject, float deltaTime);

	// Calls DrawUpdate on an object.
	void ExecuteDrawObject(GameObject* gameObject, SDL_Renderer* renderer);

	// If new objects have been created during update time,
	// this function will pass them into the object list.
	void EstablishNewObjects();

	// Deletes destroyed objects.
	void EmptyTrashCan();

private:
	void OnGameObjectEvent(GameObject* gameObject, GameObjectEventType eventType);

protected:
	// Wrapper to make sure that the delegate can always be unsubbed on deletion.
	/*GameObject::GameObjectEvent */
	GameObject::GameObjectEvent onGameObjectEventWrapper = [this](GameObject* gameObject, GameObjectEventType eventType) { OnGameObjectEvent(gameObject, eventType); };

	// Is called when the engine has booted up and 
	// initializes the game.
	virtual void InitializeGame();

	virtual void LateInitializeGame();

	// Is called on shutdown.
	virtual void UninitializeGame();

	// What will happen list-wise when a new GameObject has spawned.
	// By default, the GameObject is added to m_existingGameObjects and
	// m_enabledGameObjects.
	void _ObjectListAction_NewObject(GameObject* gameObject);

	// What will happen list-wise when a GameObject is destroyed.
	// By default, the GameObject is erased from m_enabled/existingGameObjects, 
	// then deleted.
	virtual void _ObjectListAction_DestroyedObject(GameObject* gameObject);

	// What will happen list-wise when a new GameObject is disabled.
	// By default, the GameObject is removed from m_enabledGameObjects.
	virtual void _ObjectListAction_DisabledObject(GameObject* gameObject) { }

	// What will happen list-wise when a new GameObject is enabled.
	// By default, the GameObject is added to m_enabledGameObjects.
	virtual void _ObjectListAction_EnabledObject(GameObject* gameObject) { }

	virtual Room* GameStartRoom() const { std::cout << "Null hahaha" << std::endl; return nullptr; }

public:
	virtual std::string GetGameName() const { return m_defaultBaseGameName; }

	virtual Vector2 GetScreenResolution() const { return m_defaultScreenResolution; }

	virtual float GetTimeStep() const { return m_defaultTimeStep; }

	virtual float GetDrawTimeStep() const { return m_defaultDrawTimeStep; }

	virtual float GetMaxTimeStep() const { return m_defaultMaxTimeStep; }

	/* Is called when the game starts. */
	virtual void OnGameStart() {}

	/* Is called when the game resets. Put reset-specific code in here. OnGameStart() is called in the base function. */
	virtual void OnGameReset();

	/* Returns the amount of time (in seconds) passed since the game started. */
	float Time() const;

	/* Returns the amount of time (in seconds) passed since the last frame. */
	float DeltaTime() const;

	/* Returns the game base currently carried by the engine. */
	GameBase* GetEngineGameBase() const;

	/* Returns the current room. */
	Room* GetRoom() const;
	/* Sets the current room. Room change takes place after the next update. */
	void GoToRoom(Room* room, bool rememberPreviousRoom);

	/* Returns a GameObject that currently exists in the room. index corresponds to which object in the list. */
	GameObject* GetExistingGameObjectByID(const GameObjectID gameObjectID, const int index) const;

	int GetGameObjectCount(const GameObjectID gameObjectID) const;

	bool GetAllGameObjectsByID(std::vector<GameObject*>& vector, const GameObjectID gameObjectID) const;

	//int GetExistingGameObjectsCount() const { return m_existingGameObjects.size(); }

	//int GetEnabledGameObjectsCount() const { return m_enabledGameObjects.size(); }

private:
	void Exec_GoToRoom(Room* room, bool rememberPreviousRoom);
};


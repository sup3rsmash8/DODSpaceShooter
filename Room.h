#pragma once

#include "GameObject.h"
#include <map>

/// <summary>
/// Rooms are basically scenes - they contain information about
/// what objects exist inside it and what background to use.
/// </summary>
class Room
{
	friend class GameBase;

public:
	Room();

private:
	static const std::string m_defaultLevelName;

	SDL_Rect m_view = SDL_Rect();

	// Flags whether or not the room should reload the
	// remembered object lists below when loaded.
	bool m_isRemembered = false;

	std::map<GameObjectID, std::vector<GameObject*>> m_existingObjectMapCache = std::map<GameObjectID, std::vector<GameObject*>>();

protected:
	// Is called when the room is loaded.
	virtual void OnRoomLoad();

public:
	virtual std::string GetRoomName() const { return m_defaultLevelName; }

	virtual std::map<GameObjectID, std::vector<GameObject*>> InitRoomObjects() { return std::map<GameObjectID, std::vector<GameObject*>>(); }

	// Sets the location of the "camera" in the room.
	void SetRoomView(const SDL_Rect newView);

	// Gets the location of the "camera" in the room.
	// W and H currently don't zoom in.
	SDL_Rect GetRoomView() const;
};


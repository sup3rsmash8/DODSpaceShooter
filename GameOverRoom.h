#pragma once

#include "Room.h"

class GameOverRoom : public Room
{
	static const std::string m_roomName;

public:
	virtual std::map<GameObjectID, std::vector<GameObject*>> InitRoomObjects() override;

	virtual std::string GetRoomName() const override { return m_roomName; }
};


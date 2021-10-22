#pragma once
#include "Room.h"

class TestLevel : public Room
{
	static const std::string m_roomName;

public:
	virtual std::map<GameObjectID, std::vector<GameObject*>> InitRoomObjects() override;

	virtual void OnRoomLoad() override;

	virtual std::string GetRoomName() const override { return m_roomName; }
};


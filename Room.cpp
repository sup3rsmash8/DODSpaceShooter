#include "Room.h"
#include "Statics.h"

const std::string Room::m_defaultLevelName = "Level";

Room::Room()
{
	Vector2 resolution;

	GameBase* gameBase = Statics::GetGameBase();
	if (gameBase)
	{
		resolution = gameBase->GetScreenResolution();
	}
	else
	{
		resolution = VEC2_ZERO;
	}

	//SDL_Rect rect = { 0, 0, (int)resolution.x, (int)resolution.y };

	//SetRoomView(rect);
}

void Room::OnRoomLoad()
{
	if (!m_isRemembered)
	{
		m_existingObjectMapCache = InitRoomObjects();
	}
	else
	{
		m_isRemembered = false;
	}
}

void Room::SetRoomView(const SDL_Rect newView)
{
	m_view = newView;
}

SDL_Rect Room::GetRoomView() const
{
	return m_view;
}

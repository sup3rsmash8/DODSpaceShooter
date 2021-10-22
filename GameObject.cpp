#include "GameObject.h"
#include "Statics.h"
#include <functional>
#include <iostream>

const std::string GameObject::m_defaultGameObjectName = "GameObject";
//std::vector<GameObject::GameObjectEvent> GameObject::m_gameObjectEvents = std::vector<GameObjectEvent>();
MulticastFunction<GameObject*, GameObjectEventType> GameObject::m_gameObjectEvent = MulticastFunction<GameObject*, GameObjectEventType>();

void GameObject::SetPosition(const Vector2 newPosition)
{
	m_position = newPosition;
}

void GameObject::SetRotation(const float newRotation)
{
	m_rotation = newRotation;
}

void GameObject::SetEnabled(const bool enabled)
{
	const bool previously = m_enabled;

	m_enabled = enabled;

	if (m_enabled && !previously)
	{
		OnEnabled();
		CallGameObjectEvent(this, GameObjectEventType::ENABLED);
	}
	else if (!m_enabled && previously)
	{
		OnDisabled();
		CallGameObjectEvent(this, GameObjectEventType::DISABLED);
	}
}

void GameObject::SetRender(const bool enabled)
{
	m_render = enabled;
}

GameObject::GameObject()
{
	m_position = VEC2_ZERO;
	m_rotation = 0;

	CallGameObjectEvent(this, GameObjectEventType::CREATED);
}

GameObject::GameObject(const Vector2 position, float rotation, bool enabled)
{
	m_position = position;
	m_rotation = rotation;

	CallGameObjectEvent(this, GameObjectEventType::CREATED);

	SetEnabled(enabled);
}

GameObject::~GameObject()
{
	m_instanceGameObjectEvent.Call(std::tuple<GameObjectEventType>(GameObjectEventType::DESTROYED));
	// Inform listeners that this object has been destroyed.
	CallGameObjectEvent(this, GameObjectEventType::DESTROYED);
	
}

//void GameObject::SetTextureFromFile(const char* file, std::shared_ptr<SDL_Texture>& sTexture)
void GameObject::SetTextureFromFile(const char* file, SDL_Texture*& sTexture)
{
	if (sTexture)
	{
		return;
	}

	GameEngine* engine = Statics::GetGameEngine();
	if (engine)
	{
		SDL_Renderer* renderer = engine->GetRenderer();

		if (renderer)
		{
			SDL_Surface* surface = IMG_Load(file);
			if (!surface)
			{
				std::cout << "Image loading error. Path undefined?" << std::endl;
				return;
			}

			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			if (!texture)
			{
				printf("Texture creation error: %s\n", SDL_GetError());
			}

			//sTexture = std::shared_ptr<SDL_Texture>(texture, SDL_DestroyTexture);
			sTexture = texture;

			SDL_FreeSurface(surface);
		}
		else
		{
			std::cout << "no renderer" << std::endl;
		}
	}
	else
	{
		std::cout << "no engine" << std::endl;
	}
}

bool GameObject::SubscribeGameObjectEvent(GameObjectEvent* goEvent)
{
	m_gameObjectEvent.Subscribe(goEvent);
	//for (int i = 0; i < m_gameObjectEvents.size(); i++)
	//{
	//	if (&m_gameObjectEvents[i] == &goEvent)
	//	{
	//		std::cout << "Function already subscribed." << std::endl;
	//		return false;
	//	}
	//}

	//m_gameObjectEvents.push_back(goEvent);

	return true;
}

bool GameObject::UnsubscribeGameObjectEvent(GameObjectEvent* goEvent)
{
	m_gameObjectEvent.Unsubscribe(goEvent);
	
	return true;
	//for (int i = 0; i < m_gameObjectEvents.size(); i++)
	//{
	//	if (&m_gameObjectEvents[i] == &goEvent)
	//	{
	//		m_gameObjectEvents.erase(m_gameObjectEvents.begin() + i);
	//		return true;
	//	}
	//}

	//return false;
}

void GameObject::CallGameObjectEvent(GameObject* contextObj, GameObjectEventType eventType)
{
	const std::tuple<GameObject*, GameObjectEventType> tuple = std::tuple<GameObject*, GameObjectEventType>(contextObj, eventType);
	m_gameObjectEvent.Call(tuple);
	//for (int i = 0; i < m_gameObjectEvents.size(); i++)
	//{
	//	if (m_gameObjectEvents[i])
	//		m_gameObjectEvents[i](contextObj, eventType);
	//}
}

void GameObject::Exec_Update(float deltaTime)
{
	Update(deltaTime);

	if (m_speed != VEC2_ZERO)
		SetPosition(GetPosition() + GetSpeed() * deltaTime);
}

void GameObject::Exec_DrawUpdate(SDL_Renderer* renderer)
{
	DrawUpdate(renderer);

	if (m_texture.IsRenderable())
	{
		if (GetRender())
		{
			SDL_Rect roomView = Statics::GetRoomView();

			Vector2 pos = m_position + Vector2(static_cast<float>(roomView.x), static_cast<float>(roomView.y));
			//if (!IsFixedToRoomView())
			//{
			//	pos += Vector2(roomView.x, roomView.y);
			//}

			m_texture.RenderTexture(renderer, pos, m_rotation);

			//std::cout << "I could be rendered " << GetGameObjectName() << std::endl;
		}
	}

	LateDrawUpdate(renderer);
}

void GameObject::OnEnabled()
{
	m_instanceGameObjectEvent.Call(std::tuple<GameObjectEventType>(GameObjectEventType::ENABLED));
}

void GameObject::OnDisabled()
{
	m_instanceGameObjectEvent.Call(std::tuple<GameObjectEventType>(GameObjectEventType::DISABLED));
}


void GameObject::SetXSpeed(const float xSpeed)
{
	m_speed.x = xSpeed;
}

void GameObject::AddXSpeed(const float xSpeed)
{
	m_speed.x += xSpeed;
}

bool GameObject::Subscribe_GameObjectInstanceEvent(GameObjectInstanceEvent* goInstEvent)
{
	if (!goInstEvent)
		return false;

	m_instanceGameObjectEvent.Subscribe(goInstEvent);

	return true;
}

bool GameObject::Unsubscribe_GameObjectInstanceEvent(GameObjectInstanceEvent* goInstEvent)
{
	if (!goInstEvent)
		return false;

	m_instanceGameObjectEvent.Unsubscribe(goInstEvent);

	return true;
}

void GameObject::SetYSpeed(const float ySpeed)
{
	m_speed.y = ySpeed;
}

void GameObject::AddYSpeed(const float ySpeed)
{
	m_speed.y += ySpeed;
}

void GameObject::SetSpeed(const Vector2 speed)
{
	m_speed = speed;
}

void GameObject::AddSpeed(const Vector2 speed)
{
	m_speed += speed;
}
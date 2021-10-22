#pragma once

#include "Library.h"
#include <functional>
#include <vector>
#include <string>
#include "MulticastFunction.h"
#include "GameTexture.h"
#include "GameObjectID.h"

enum class GameObjectEventType
{
	CREATED = 0, // The GameObject was created (not necessarily enabled).
	ENABLED = 1, // The GameObject was enabled.
	DISABLED = 2, // The GameObject was disabled.
	DESTROYED = 3, // The GameObject was deleted.
};

class GameObject
{
	friend class GameBase;

public:
	GameObject();
	GameObject(const Vector2 position, float rotation = 0, bool enabled = true);
	virtual ~GameObject();

	typedef std::function<void(GameObject*, GameObjectEventType)> GameObjectEvent;
	typedef std::function<void(GameObjectEventType)> GameObjectInstanceEvent;
private:
	//static std::vector<GameObjectEvent> m_gameObjectEvents;

	static MulticastFunction<GameObject*, GameObjectEventType> m_gameObjectEvent;

	static const std::string m_defaultGameObjectName;//"GameObject"

	MulticastFunction<GameObjectEventType> m_instanceGameObjectEvent = MulticastFunction<GameObjectEventType>();

	bool m_fixedToRoomView = false;

	Vector2 m_position = VEC2_ZERO;

	Vector2 m_speed = VEC2_ZERO;

	float m_rotation = 0;

	bool m_enabled = true;

	bool m_render = true;

	bool m_isMarkedForDestruction = false;

protected:
	GameTexture m_texture;

private:
	static void CallGameObjectEvent(GameObject* contextObj, GameObjectEventType eventType);

protected:
	/*void SetTextureFromFile(const char* file, std::shared_ptr<SDL_Texture>& sTexture);*/

	// Loads a texture located at file and appends it to the sTexture pointer.
	// NOTE: The pointer must be a nullptr for the texture to load. 
	void SetTextureFromFile(const char* file, SDL_Texture*& sTexture);

public:
	/// <summary>
	/// Subscribes to the event that fires when a GameObject 
	/// (could be any) is constructed, enabled, disabled or destructed.
	/// Returns true if this succeeds, false if already subscribed or
	/// failed otherwise.
	/// </summary>
	static bool SubscribeGameObjectEvent(GameObjectEvent* goEvent);

	/// <summary>
	/// Returns false if the event was never subscribed to begin with.
	/// </summary>
	static bool UnsubscribeGameObjectEvent(GameObjectEvent* goEvent);

	bool Subscribe_GameObjectInstanceEvent(GameObjectInstanceEvent* goInstEvent);

	bool Unsubscribe_GameObjectInstanceEvent(GameObjectInstanceEvent* goInstEvent);

	virtual std::string GetGameObjectName() { return m_defaultGameObjectName; }

	/* Returns the ID of this object. */
	virtual GameObjectID GetID() const = 0;

	///* Returns the number of objects allowed to exist simultaneously in a scene. */
	//virtual int GetMaxExistingObjects() const = 0;

	// Will this GameObject be destroyed at the end of this frame?
	bool IsMarkedForDestruction() const { return m_isMarkedForDestruction; }

	bool IsEnabled() const { return m_enabled; }

	// Returns whether this object is rendered 
	// with the room view (like a GUI element) or not.
	bool IsFixedToRoomView() const { return m_fixedToRoomView; }

	// Marks the GameObject for destruction at the end of the update cycle.
	// (NOTE: This should ALWAYS be called as opposed to deleting GameObjects manually!)
	void Destroy() { m_isMarkedForDestruction = true; }

	// Sets whether this object is rendered 
	// with the room view (like a GUI element) or not.
	void SetFixedToRoomView(const bool fixed) { m_fixedToRoomView = fixed; }

	void SetEnabled(const bool enabled);
	bool GetEnabled() const { return m_enabled; }

	void SetRender(const bool enabled);
	bool GetRender() const { return m_render; }

private:
	void Exec_Update(float deltaTime);

	void Exec_DrawUpdate(SDL_Renderer* renderer);

protected:
	// Is called when the object has been successfully established after creation.
	// Creation of objects, like colliders, go here, as this is called during establishment time.
	virtual void OnEstablished() {}

	// Is called once every frame. Put object logic here.
	virtual void Update(float deltaTime) {}

	// Is called right before this object gets drawn.
	virtual void DrawUpdate(SDL_Renderer* renderer) {}

	// Is called after this object is drawn.
	virtual void LateDrawUpdate(SDL_Renderer* renderer) {}

	virtual void OnEnabled();

	virtual void OnDisabled();

	Vector2 GetSpeed() const { return m_speed; }

	void SetXSpeed(const float xSpeed);
	void AddXSpeed(const float xSpeed);

	void SetYSpeed(const float ySpeed);
	void AddYSpeed(const float ySpeed);

	void SetSpeed(const Vector2 speed);
	void AddSpeed(const Vector2 speed);

public:
	Vector2 GetPosition() const { return m_position; }
	void SetPosition(const Vector2 newPosition);

	float GetRotation() const { return m_rotation; }
	void SetRotation(const float newRotation);



	SDL_Texture* GetTexture() const { return m_texture.texture/*.get()*/; }

	Vector2 GetTextureOrigin() const { return m_texture.origin; }

	Vector2 GetTextureSize() const { return m_texture.size; }
};


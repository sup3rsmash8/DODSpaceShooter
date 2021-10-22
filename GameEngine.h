#pragma once

#include "SDL.h"
#include <typeinfo>
#include <functional>
#include <map>

class GameBase;
class Input;
class Collider;

/// <summary>
/// Handles the main process of the game, i.e. the core initializations of SDL and the game class,
/// as well as being the class closest to main(). Do not create new instances of this anywhere in 
/// your game outside of main().
/// </summary>
class GameEngine final
{
public:
	GameEngine(GameBase* gameBase);
	~GameEngine();

	void Initialize();
	void Uninitialize();

private:
	// Event for when the game updates on a step.
	typedef std::function<void(float)> UpdateEvent;
	// Event for when the game updates a frame.
	typedef std::function<void()> DrawUpdateEvent;

	bool m_applicationRunning = false;

	float m_time = 0; // Returns the amount of time (in seconds) passed since the game started.
	float m_deltaTime = 0; // The amount of time(in seconds) passed since the last frame.
	float m_accumulatedTime = 0; // The time passed since the last iteration Update() was called.
	float m_accumulatedDrawTime = 0; // The time passed since the last iteration DrawUpdate() was called.
	Uint64 m_previousTicks = 0;

	SDL_Event m_evt = SDL_Event();

	SDL_Renderer* m_renderer = nullptr;
	
	SDL_Window* m_window = nullptr;

	SDL_Thread* m_particleThread = nullptr;

	SDL_Thread* m_collisionThread = nullptr;

	GameBase* m_gameBase = nullptr;

	Input* m_input = nullptr;

public:
	/* The core game loop called in main(). Do NOT call this outside it! */
	void GameLoop();

	bool Input_GetKey(SDL_Keycode keyCode) const;

	bool Input_GetKeyDown(SDL_Keycode keyCode) const;

	bool Input_GetKeyUp(SDL_Keycode keyCode) const;

	/* Returns the amount of time (in seconds) passed since the game started. */
	float Time() const { return m_time; }

	/* Returns the amount of time (in seconds) passed since the last frame. */
	float DeltaTime() const { return m_deltaTime; }

	GameBase* GetGameBase() const { return m_gameBase; }

	SDL_Renderer* GetRenderer() const { return m_renderer; }

private:
	void Start();
	
	void Update(float deltaTime);

	void DrawUpdate(SDL_Renderer* renderer);

	// The main GameObject update procedure
	void UpdateProcess(float& timeStep, float& accumulatedTime, float& deltaTime);

	// Establishment of newly created GameObjects, deletion of trashed GameObjects
	void PostUpdateProcess();

	// Rendering of objects
	void UpdateDrawProcess(float& timeStep, float& accumulatedTime);

	// Triggers collision events between each key and value.
	void CollisionCheck(std::map<Collider*, Collider*>& collisions);
};


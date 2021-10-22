#pragma once

#include "Input.h"

inline bool Input_GetKey(SDL_Keycode keyCode)
{
	GameEngine* engine = Statics::GetGameEngine();

	return engine && engine->Input_GetKey(keyCode);
}

inline bool Input_GetKeyDown(SDL_Keycode keyCode)
{
	GameEngine* engine = Statics::GetGameEngine();

	return engine && engine->Input_GetKeyDown(keyCode);
}

inline bool Input_GetKeyUp(SDL_Keycode keyCode)
{
	GameEngine* engine = Statics::GetGameEngine();

	return engine && engine->Input_GetKeyUp(keyCode);
}
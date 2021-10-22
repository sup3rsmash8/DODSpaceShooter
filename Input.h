#pragma once

#include "SDL.h"
#include "InputState.h"
#include "Statics.h"
#include <map>

//#define GENERATE_INPUT() \

struct InputKey
{
	InputState m_inputState;
};

class Input
{
public:
	Input();

private:
	std::map<SDL_Keycode, InputKey> m_inputMaps = std::map<SDL_Keycode, InputKey>();

public:
	void RegisterInput(SDL_Event sdlEvent);

	void UpdateHeldReleased();

	bool GetKey(const SDL_Keycode keyCode) const;

	bool GetKeyDown(SDL_Keycode keyCode) const;

	bool GetKeyUp(SDL_Keycode keyCode) const;
};
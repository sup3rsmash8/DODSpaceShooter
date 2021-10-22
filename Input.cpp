#include "Input.h"

#define KEY(KCD) \
{ KCD, InputKey() } \

Input::Input()
{
	m_inputMaps = std::map<SDL_Keycode, InputKey>
	{
		KEY(SDLK_UP),
		KEY(SDLK_DOWN),
		KEY(SDLK_LEFT),
		KEY(SDLK_RIGHT),
		KEY(SDLK_SPACE),
	};
}

void Input::RegisterInput(SDL_Event sdlEvent)
{
	bool state;

	if (sdlEvent.type == SDL_KEYDOWN)
	{
		state = true;
	}
	else if (sdlEvent.type == SDL_KEYUP)
	{
		state = false;
	}
	else 
	{
		return;
	}

	SDL_Keycode code = sdlEvent.key.keysym.sym;

	// Stop if not found
	if (m_inputMaps.find(code) == m_inputMaps.end())
	{
		return;
	}

	if (state)
	{
		switch (m_inputMaps[code].m_inputState)
		{
		case InputState::NONE:
			m_inputMaps[code].m_inputState = InputState::PRESSED;
			break;

		case InputState::PRESSED:
			m_inputMaps[code].m_inputState = InputState::HELD;
			break;
		}
		//m_inputMaps[code].m_inputState
	}
	else
	{
		switch (m_inputMaps[code].m_inputState)
		{
		case InputState::HELD:
			m_inputMaps[code].m_inputState = InputState::RELEASED;
			break;

		case InputState::PRESSED:
		case InputState::RELEASED:
			m_inputMaps[code].m_inputState = InputState::NONE;
			break;
		}
	}
}

void Input::UpdateHeldReleased()
{
	for (auto& pair : m_inputMaps)
	{
		if (pair.second.m_inputState == InputState::PRESSED)
		{
			pair.second.m_inputState = InputState::HELD;
		}
		else if (pair.second.m_inputState == InputState::RELEASED)
		{
			pair.second.m_inputState = InputState::NONE;
		}
	}
}

bool Input::GetKey(const SDL_Keycode keyCode) const
{
	if (m_inputMaps.find(keyCode) == m_inputMaps.end())
	{
		std::cout << "Key does not exist." << std::endl;
		return false;
	}

	InputKey key = m_inputMaps.at(keyCode);

	return key.m_inputState == InputState::PRESSED || key.m_inputState == InputState::HELD;
}

bool Input::GetKeyDown(SDL_Keycode keyCode) const
{
	if (m_inputMaps.find(keyCode) == m_inputMaps.end())
	{
		std::cout << "Key does not exist." << std::endl;
		return false;
	}

	InputKey key = m_inputMaps.at(keyCode);

	return key.m_inputState == InputState::PRESSED;
}

bool Input::GetKeyUp(SDL_Keycode keyCode) const
{
	if (m_inputMaps.find(keyCode) == m_inputMaps.end())
	{
		std::cout << "Key does not exist." << std::endl;
		return false;
	}

	InputKey key = m_inputMaps.at(keyCode);

	return key.m_inputState == InputState::RELEASED;
}


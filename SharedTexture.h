#pragma once

#include "SDL_image.h"

struct SharedTexture
{
	SharedTexture(SDL_Texture* texture);

private:
	SDL_Texture* m_texture;
	int m_users;

public:
	void operator=(SharedTexture a);
};


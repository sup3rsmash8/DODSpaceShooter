#pragma once

#include "Library.h"
#include "SDL.h"
#include "SDL_image.h"
#include <memory>

struct GameTexture
{
	GameTexture();
	GameTexture(SDL_Texture* texture, const Vector2 size, const Vector2 origin);
	//GameTexture(std::shared_ptr<SDL_Texture> texture, const Vector2 size, const Vector2 origin);

	SDL_Texture*/*std::shared_ptr<SDL_Texture>*/ texture;
	Vector2 origin;
	Vector2 size;

	void RenderTexture(SDL_Renderer* renderer, const Vector2& position, const Vector2& size, const float rot);

	void RenderTexture(SDL_Renderer* renderer, const Vector2& position, const Vector2& size, const float rot, const Vector2& origin);

	void RenderTexture(SDL_Renderer* renderer, const Vector2& position, const float rot);

	bool IsRenderable() const { return texture != nullptr && size.x != 0 && size.y != 0; }
};


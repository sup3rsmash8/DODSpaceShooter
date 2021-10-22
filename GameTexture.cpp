#include "GameTexture.h"

GameTexture::GameTexture()
{
	this->texture = nullptr;
	this->size = { 0, 0 };
	this->origin = { 0, 0 };
}

GameTexture::GameTexture(SDL_Texture* texture, const Vector2 size, const Vector2 origin)
{
	this->texture = texture;
	this->size = size;
	this->origin = origin;
}

//GameTexture::~GameTexture()
//{
//	if (texture)
//	{
//		SDL_DestroyTexture(texture);
//	}
//}

void GameTexture::RenderTexture(SDL_Renderer* renderer, const Vector2& pos, const Vector2& size, const float rot)
{
	RenderTexture(renderer, pos, size, rot, origin);
}

void GameTexture::RenderTexture(SDL_Renderer* renderer, const Vector2& pos, const Vector2& size, const float rot, const Vector2& origin)
{
	if (!renderer)
	{
		printf("no render :(\n");
		return;
	}

	SDL_Rect rect = { pos.x - size.x * origin.x, pos.y - size.y * origin.y, size.x, size.y };

	//if (SDL_RenderCopyEx(renderer, texture.get(), NULL, &rect, rot, NULL, SDL_FLIP_NONE) == -1)
	if (SDL_RenderCopyEx(renderer, texture, NULL, &rect, rot, NULL, SDL_FLIP_NONE) == -1)
	{
		printf("Error render: %s\n", SDL_GetError());
	}
}

void GameTexture::RenderTexture(SDL_Renderer* renderer, const Vector2& position, const float rot)
{
	if (!renderer)
	{
		printf("no render :(\n");
		return;
	}

	RenderTexture(renderer, position, size, rot);
}


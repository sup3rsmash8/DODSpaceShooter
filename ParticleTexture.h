#pragma once

#include "Library.h"
#include "SDL.h"
#include <memory>

struct ParticleTexture
{
	ParticleTexture()
	{
		this->m_texture = nullptr;
		this->m_cellSize = { 0, 0 };
		this->m_frameCount = 0;
	}

	/*ParticleTexture(std::shared_ptr<SDL_Texture> texture, Vector2Int cellSize, uint32_t frameCount)*/
	ParticleTexture(SDL_Texture* texture, Vector2Int cellSize, uint32_t frameCount)
	{
		this->m_texture = texture;
		this->m_cellSize = cellSize;
		this->m_frameCount = frameCount;
	}
	/*std::shared_ptr<SDL_Texture> m_texture;*/
	SDL_Texture* m_texture;
	Vector2Int m_cellSize;
	uint32_t m_frameCount;
};
#include "TextObject.h"
#include "Statics.h"
#include "SpaceShooterGame.h"

//std::vector<TTF_Font> TextObject::m_loadedFonts = std::vector<TTF_Font>();

TextObject::TextObject(const Vector2 position, float rotation, bool enabled, std::string text, TTF_Font* font, SDL_Color color) : GameObject(position, rotation, enabled)
{
	if (text.size() > 0 && font)
		SetText(text, font, color);

	
	SetFixedToRoomView(true);
}

TextObject::~TextObject()
{
	if (m_texture.texture)
	{
		SDL_DestroyTexture(m_texture.texture/*.get()*/);
	}
}

bool TextObject::SetText(std::string text, TTF_Font* font, SDL_Color color)
{
	// Free previous text(ure) HAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHA
	if (m_texture.texture)
	{
		SDL_DestroyTexture(m_texture.texture/*.get()*/);
	}

	if (!font)
	{
		std::cout << "Text could not be rendered: No font was provided." << std::endl;
		return false;
	}

	SDL_Renderer* renderer = Statics::GetGameEngine()->GetRenderer();

	if (renderer)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

		//m_textTexture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, surface), SDL_DestroyTexture);
		m_textTexture = SDL_CreateTextureFromSurface(renderer, surface);

		if (!m_textTexture)
		printf("Texture creation error: %s\n", SDL_GetError());
		
		m_texture = GameTexture(m_textTexture, Vector2(static_cast<float>(surface->w), static_cast<float>(surface->h)), VEC2_ONE * .5f);

		SDL_FreeSurface(surface);

		return true;
	}
	else
	{
		std::cout << "Text could not be rendered: No renderer was found." << std::endl;
	}

	return false;
}

void TextObject::Update(float deltaTime)
{

}

void TextObject::DrawUpdate(SDL_Renderer* renderer)
{

}

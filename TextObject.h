#pragma once

#include "GameObject.h"
#include "SDL_ttf.h"

class TextObject : public GameObject
{
public:
	TextObject(const Vector2 position, float rotation = 0, bool enabled = true, std::string text = "", TTF_Font* font = nullptr, SDL_Color color = { 255, 255, 255, 255 });

	~TextObject();

private:
	SDL_Texture* m_textTexture = nullptr;

public:
	bool SetText(std::string text, TTF_Font* font, SDL_Color color = { 255, 255, 255, 255 });

	virtual void Update(float deltaTime) override;
	virtual void DrawUpdate(SDL_Renderer* renderer) override;

	virtual std::string GetGameObjectName() override { return "TextObject"; }

	virtual GameObjectID GetID() const override { return GameObjectID::TEXT_OBJECT; }

	/*virtual int GetMaxExistingObjects() const override { return 50; }*/
};


#pragma once
#include "spriteComponent.h"
#include <vector>
#include "MathForGames.h"


class BGSpriteComponent : public spriteComponent
{
public:
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	
	void update(float DeltaTime) override;
	void draw(SDL_Renderer* Renderer) override;

	void SetBGTextures(const std::vector<SDL_Texture*>& textures);

	void SetScreenSize(const Vector2D& size) { screenSize = size; }
	void SetScrollSpeed(float speed) { scrollSpeed = speed; }
	float GetScrollSpeed() const { return scrollSpeed; }

private:
	struct BGTexture
	{
		SDL_Texture* Texture;
		Vector2D offset;
	};
	std::vector<BGTexture> vBGTextures;
	Vector2D screenSize;
	float scrollSpeed;
};
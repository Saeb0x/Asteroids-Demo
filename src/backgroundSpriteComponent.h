#pragma once
#include "spriteComponent.h"
#include "MathForGames.h"
#include <vector>

class backgroundSpriteComponent : public spriteComponent
{
public:
	// lower draw order since this is the background, it has to be drawn furthur back
	backgroundSpriteComponent(class Actor* ownerActor, int drawOrder = 10);

	void update(float DeltaTime) override;
	void draw(SDL_Renderer* Renderer) override;
	void setBGTextures(const std::vector<SDL_Texture*>& textures);

	void setScreenSize(const Vector2D& size) { screenSize = size; }
	void setScrollSpeed(float speed) { scrollSpeed = speed; }
	float getScrollSpeed() const { return scrollSpeed; }

private:
	// to encapsulate each BG image and it's offset
	struct bgTexture
	{
		SDL_Texture* Texture;
		Vector2D offset;
	};
	std::vector<SDL_Texture*> vBGTextures;
	Vector2D screenSize;
	float scrollSpeed;
};



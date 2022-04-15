#include "backgroundSpriteComponent.h"
#include "Actor.h"

backgroundSpriteComponent::backgroundSpriteComponent(Actor* ownerActor, int drawOrder) : spriteComponent(ownerActor, drawOrder), scrollSpeed(0.0f)
{
};

void backgroundSpriteComponent::setBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto texture : textures)
	{
		bgTexture temp;
		temp.Texture = texture;
		
		// Each texture equals screen width in offset
		temp.offset.x = count * screenSize.x;

		temp.offset.y = 0;

		vBGTextures.emplace_back(temp);
		count++;
	}
}
#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder) : spriteComponent(owner, drawOrder), scrollSpeed(0.0f)
{
}

void BGSpriteComponent::update(float DeltaTime)
{
	spriteComponent::update(DeltaTime);
	for (auto& BG : vBGTextures)
	{
		BG.offset.x += scrollSpeed * DeltaTime;
		
		if (BG.offset.x < -screenSize.x)
		{
			BG.offset.x = (vBGTextures.size() - 1) * screenSize.x - 1;
		}
	}
}

void BGSpriteComponent::draw(SDL_Renderer* renderer)
{
	for (auto& BG : vBGTextures)
	{
		SDL_Rect rect;
		
		rect.w = static_cast<int>(screenSize.x);
		rect.h = static_cast<int>(screenSize.y);
		
		rect.x = static_cast<int>(ownerActor->GetPosition().x - rect.w / 2 + BG.offset.x);
		rect.y = static_cast<int>(ownerActor->GetPosition().y - rect.h / 2 + BG.offset.y);

		SDL_RenderCopy(renderer, BG.Texture, nullptr, &rect);
	}
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto texture : textures)
	{
		BGTexture temporary;
		temporary.Texture = texture;
		
		temporary.offset.x = count * screenSize.x;
		temporary.offset.y = 0;
		vBGTextures.emplace_back(temporary);
		count++;
	}
}

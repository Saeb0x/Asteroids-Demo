#pragma once
#include "spriteComponent.h"
#include <vector>

class animatedSpriteComponent : public spriteComponent
{
public:
	animatedSpriteComponent(class Actor* owner, int drawOrder = 100);

	void update(float DeltaTime) override;

	void setAnimationTextures(const std::vector<SDL_Texture*>& textures);

	float getAnimationFPS() const { return AnimationFPS; }
	void setAnimationFPS(float FPS) { AnimationFPS = FPS; }
private:
	std::vector<SDL_Texture*> vAnimationTextures;
	
	float currentFrame; 
	
	float AnimationFPS;
};
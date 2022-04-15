#pragma once
#include "Actor.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);
	void updateActor(float DeltaTime) override;
	void actorInput(const uint8_t* state) override;
private:
	float laserCoolDown;
	class CircleComponent* aCircle;
};
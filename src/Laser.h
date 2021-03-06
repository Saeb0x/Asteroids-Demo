#pragma once
#include "Actor.h"

class Laser : public Actor
{
public:
	Laser(class Game* game);
	void updateActor(float deltaTime) override;
private:
	class CircleComponent* lCircle;
	float DeathTimer;
};

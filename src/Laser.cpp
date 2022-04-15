#include "Laser.h"
#include "spriteComponent.h"
#include "moveComponent.h"
#include "Game.h"
#include "circleComponent.h"
#include "Asteroids.h"

Laser::Laser(Game* game) : Actor(game), DeathTimer(1.0f)
{
	//sprite component
	spriteComponent* SC = new spriteComponent(this);
	SC->setTexture(game->getTexture("Assets/Laser.png"));

	// move component with a forward speed
	MoveComponent* moveComponent = new MoveComponent(this);
	moveComponent->setForwardSpeed(800.0f);

	// circle component, for collision
	lCircle = new CircleComponent(this);
	lCircle->setRadius(11.0f);
}

void Laser::updateActor(float deltaTime)
{
	// If run out of time, laser dies
	DeathTimer -= deltaTime;
	if (DeathTimer <= 0.0f)
	{
		SetState(State::Dead);
	}
	else
	{
		for (auto asteroid : getGame()->GetAsteroids())
		{
			if (Intersection(*lCircle, *(asteroid->GetCircle())))
			{
				// laser intersects with an asteroid
				SetState(State::Dead);
				asteroid->SetState(State::Dead);
				break;
			}
		}
	}
}

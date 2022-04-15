#include "Ship.h"
#include "spriteComponent.h"
#include "inputComponent.h"
#include "circleComponent.h"
#include "Game.h"
#include "Asteroids.h"
#include "Laser.h"

Ship::Ship(Game* game) : Actor(game), laserCoolDown(0.0f)
{
	// sprite component
	spriteComponent* SC = new spriteComponent(this,150);
	SC->setTexture(game->getTexture("Assets/Ship.png"));

	// Create an input component and set keys and speed
	InputComponent* inputComponent = new InputComponent(this);
	inputComponent->setForwardKey(SDL_SCANCODE_W);
	inputComponent->setBackKey(SDL_SCANCODE_S);
	inputComponent->setClockwiseKey(SDL_SCANCODE_A);
	inputComponent->setCounterClockwiseKey(SDL_SCANCODE_D);
	inputComponent->setMaxForwardSpeed(300.0f);
	inputComponent->setMaxAngularSpeed(BasicMath::TwoPI);

	// circle component, for collision
	aCircle = new CircleComponent(this);
	aCircle->setRadius(11.0f);

}

void Ship::updateActor(float deltaTime)
{
	laserCoolDown -= deltaTime;
	for (auto asteroid : getGame()->GetAsteroids())
	{
		if (Intersection(*aCircle, *(asteroid->GetCircle())))
		{
			// player's ship intersects with an asteroid
			SetState(State::Dead);
			asteroid->SetState(State::Dead);
			SetPosition(Vector2D(512.0f, 384.0f));
			SetRotation(0);
			SetState(State::Active);
			break;
		}
	}
}

void Ship::actorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && laserCoolDown <= 0.0f)
	{
		// a laser with it's position and rotation
		Laser* laser = new Laser(getGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		laserCoolDown = 0.3f;
	}
}

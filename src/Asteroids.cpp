#include "Asteroids.h"
#include "Game.h"
#include "spriteComponent.h"
#include "moveComponent.h"
#include "circleComponent.h"
#include "Random.h"

Asteroid::Asteroid(Game* game) : Actor(game), mCircle(nullptr)
{
	
	Vector2D randPos = Random::getVector(Vector2D::Zero,Vector2D(1024.0f, 768.0f));
	SetPosition(randPos);

	SetRotation(Random::getFloatRange(0.0f, BasicMath::TwoPI));

	spriteComponent* SC = new spriteComponent(this);
	SC->setTexture(game->getTexture("Assets/Asteroid.png"));

	MoveComponent* moveComponent = new MoveComponent(this);
	moveComponent->setForwardSpeed(150.0f);
	
	mCircle = new CircleComponent(this);
	mCircle->setRadius(40.0f);

	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	getGame()->RemoveAsteroid(this);
}
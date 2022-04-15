#include "Game.h"
#include "Actor.h"
#include "spriteComponent.h"
#include "BGspriteComponent.h"
#include "Ship.h"
#include "Asteroids.h"
#include <algorithm>
#include <SDL_image.h>

Game::Game() : Window(nullptr), Renderer(nullptr), EngineIsRunning(true), UpdatingActors(false), TicksCount(0), mShip(nullptr) {}

bool Game::initialization()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Failed to initialize SDL subsystems: %s", SDL_GetError());
		return false;
	}

	Window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, 0);
	if (!Window)
	{
		SDL_Log("Failed to create a window!");
		return false;
	}

	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!Renderer)
	{
		SDL_Log("Failed to create a renderer!");
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Failed to initialize SDL image: %s", SDL_GetError());
		return false;
	}

	loadData();

	TicksCount = SDL_GetTicks();

	return true;
}

void Game::gameLoop()
{
	while (EngineIsRunning)
	{
		processInputs();
		updateGame();
		generateOutput();
	}
}

void Game::processInputs()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			EngineIsRunning = false;
			break;
		}
	}

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		EngineIsRunning = false;
	}

	// process inputs
	UpdatingActors = true;
	for (auto actor : vActors)
	{
		actor->processInput(keyboardState);
	}
	UpdatingActors = false;
}

void Game::updateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), TicksCount + 16));
	
	float DeltaTime = (SDL_GetTicks() - TicksCount) / 1000.0f;
	if (DeltaTime > 0.05f)
	{
		DeltaTime = 0.05f;
	}
	TicksCount = SDL_GetTicks();
	
	UpdatingActors = true;
	for (auto actor : vActors)
	{
		actor->update(DeltaTime);
	}
	UpdatingActors = false;

	for (auto pendingActor : vPendingActors)
	{
		vActors.emplace_back(pendingActor);
	}
	vPendingActors.clear();

	std::vector<Actor*> vDeadActors;
	for (auto deadActor : vActors)
	{
		if (deadActor->GetState() == Actor::State::Dead)
		{
			vDeadActors.emplace_back(deadActor);
		}
	}

	for (auto deadActor : vDeadActors)
	{
		delete deadActor;
	}
}

void Game::generateOutput()
{
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer);

	for (auto sprite : vSprites)
	{
		sprite->draw(Renderer);
	}

	SDL_RenderPresent(Renderer);
}

void Game::loadData()
{
	// player's ship
	mShip = new Ship(this);
	mShip->SetPosition(Vector2D(512.0f, 384.0f));
	mShip->SetRotation(BasicMath::PIOverTwo);

	// asteroids
	const int numAsteroids = 20;
	for (int i = 0; i < numAsteroids; i++)
	{
		new Asteroid(this);
	}
}

void Game::unloadData()
{
	// delete actors
	while (!vActors.empty())
	{
		delete vActors.back();
	}

	// destroy textures
	for (auto index : mTextures)
	{
		SDL_DestroyTexture(index.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::getTexture(const std::string& fileName)
{
	SDL_Texture* texture = nullptr;

	auto vIterator = mTextures.find(fileName);
	if (vIterator != mTextures.end())
	{
		texture = vIterator->second;
	}
	else 
	{
		SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
		if (!tempSurface)
		{
			SDL_Log("Failed to load texture file: %s", fileName.c_str());
			return nullptr;
		}

		texture = SDL_CreateTextureFromSurface(Renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		if (!texture)
		{
			SDL_Log("A failure occured while converting the surface to a texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), texture);
	}
	return texture;
}

void Game::addActor(Actor* actor)
{
	if (UpdatingActors)
	{
		vPendingActors.emplace_back(actor);
	}
	else
	{
		vActors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	auto vIterator = std::find(vPendingActors.begin(), vPendingActors.end(), actor);
	if (vIterator != vPendingActors.end())
	{
		std::iter_swap(vIterator, vPendingActors.end() - 1);
		vPendingActors.pop_back();
	}

	vIterator = std::find(vActors.begin(), vActors.end(), actor);
	if (vIterator != vActors.end())
	{
		std::iter_swap(vIterator, vActors.end() - 1);
		vActors.pop_back();
	}
}

void Game::addSprite(spriteComponent* sprite)
{
	int DrawOrder = sprite->getDrawOrder();
	auto vIterator = vSprites.begin();
	for (; vIterator != vSprites.end(); ++vIterator)
	{
		if (DrawOrder < (*vIterator)->getDrawOrder())
		{
			break;
		}
	}

	vSprites.insert(vIterator, sprite);
}

void Game::removeSprite(spriteComponent* sprite)
{
	auto vIterator = std::find(vSprites.begin(), vSprites.end(), sprite);
	vSprites.erase(vIterator);
}

void Game::AddAsteroid(Asteroid* asteroid)
{
	vAsteroids.emplace_back(asteroid);
}

void Game::RemoveAsteroid(Asteroid* asteroid)
{
	auto vIterator = std::find(vAsteroids.begin(), vAsteroids.end(), asteroid);
	if (vIterator != vAsteroids.end())
	{
		vAsteroids.erase(vIterator);
	}
}

void Game::shutDown()
{
	unloadData();
	IMG_Quit();
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}
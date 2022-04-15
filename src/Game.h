#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>

class Game
{
public:
	Game();
	bool initialization();
	void gameLoop();
	void shutDown();

	void addActor(class Actor* actor);
	void removeActor(class Actor* actor);

	void addSprite(class spriteComponent* sprite);
	void removeSprite(class spriteComponent* sprite);


	SDL_Texture* getTexture(const std::string& fileName);

	// Game specific 
	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return vAsteroids; }

private:
	void processInputs();
	void updateGame();
	void generateOutput();
	void loadData();
	void unloadData();

	SDL_Window* Window;
	SDL_Renderer* Renderer; 
	Uint32 TicksCount;
	bool EngineIsRunning;
	
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<class Actor*> vActors;
	std::vector<class Actor*> vPendingActors;
	bool UpdatingActors;

	std::vector<class spriteComponent*> vSprites;


	// Game specific
	class Ship* mShip; // player's ship
	std::vector<class Asteroid*> vAsteroids;
};
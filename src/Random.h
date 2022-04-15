#pragma once
#include <random>
#include "MathForGames.h"

class Random
{
public:
	static void initialization();

	// seed the generator with the specified integer
	static void seed(unsigned int seed);

	// get a float between 0.0f and 1.0f
	static float getFloat();

	// get a float from the specified range
	static float getFloatRange(float min, float max);

	// get an int from the specified range
	static int getIntRange(int min, int max);

	// get a random vector given the min/max bounds
	static Vector2D getVector(const Vector2D& min, const Vector2D& max);

private:
	static std::mt19937 sGenerator; // mersenne Twister 19937 generator
};
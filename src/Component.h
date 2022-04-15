#pragma once
#include <cstdint>

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100); 
	virtual ~Component();
	
	virtual void update(float DeltaTime);

	virtual void processInput(const uint8_t* keyState) {}

	int GetUpdateOrder() const { return UpdateOrder; }

protected:
	class Actor* ownerActor;
	int UpdateOrder;
};
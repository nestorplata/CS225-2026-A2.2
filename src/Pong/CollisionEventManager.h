#pragma once
#include "..\Framework\event_handlers.hh"
#include "..\Pong\Singleton.h"

class OnCollisionEvent :public Event
{
public:
	std::string ObjectName;
	AEContact* pResult = nullptr;
};

class CollisionEventManager : public EventManager, public Singleton<CollisionEventManager>
{
private:

public:
	void update() override{};

};
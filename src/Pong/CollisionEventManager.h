#pragma once
#include "..\Framework\event_handlers.hh"
#include "..\Pong\Singleton.h"

class OnCollisionEvent :public Event
{
public:
	std::string ObjectName;
	AEContact* pResult = nullptr;
public:
	OnCollisionEvent()
	{
		Event::Event();
		pResult = new AEContact();
	}

};

class CollisionEventManager : public EventManager
{
private:

public:
	CollisionEventManager() {};

	void update() override{};

};
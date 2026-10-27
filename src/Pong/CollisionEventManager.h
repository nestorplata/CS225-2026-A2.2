#pragma once
#include "..\Pong\LoopingEventManager.h"

class OnCollisionEvent :public Event
{
public:
	std::string ObjectName;
	AEContact* pResult = nullptr;
	void* ptr_object = nullptr;
public:
	OnCollisionEvent()
	{
		pResult = new AEContact();
	}
};

class OnTriggerEvent :public Event
{
public:
	PositionComponent* posComponent;
};


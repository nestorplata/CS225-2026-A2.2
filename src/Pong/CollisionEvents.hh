#pragma once
#include <iostream>
#include <AEEngine.h>
#include "..\Pong\LoopingEventManager.hh"
#include "..\Components\position_component.hh"


//simple Collision Event
//stores collision information
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
	~OnCollisionEvent()
	{
		delete (pResult);
	}
};



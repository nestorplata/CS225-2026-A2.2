#pragma once
#include "..\Framework\event_handlers.hh"
#include "Singleton.h"


class CollisionEvent :public Event
{


};

class InputEventManager : public EventManager,public  Singleton<InputEventManager>
{
private:

public:
	void update() override
	{

	}





};
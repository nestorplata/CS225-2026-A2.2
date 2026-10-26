#pragma once
#include "..\Framework\event_handlers.hh"
#include "Singleton.h"



class InputEventManager : public EventManager
{
private:

public:
	InputEventManager() {};
	

	void update() override
	{

	}
};


struct Action
{
	bool IsActionHappening;
};

class OnInputChangeEvent : public Event
{
private:

public:
	Action* MovingUp;
	Action* MovingDown;


public:

	OnInputChangeEvent()
	{
		MovingUp = new Action();
		MovingDown = new Action();
	}


	~OnInputChangeEvent()
	{
		delete(MovingUp);
		delete(MovingDown);
	}

};

class UpdateEvent : public Event
{
};
#pragma once
#include "..\Pong\LoopingEventManager.h"
#include "Singleton.h"



class InputEventManager : public LoopingEventManager 
{
public:

public:

};


struct Action
{
	bool IsActionHappening;
};

class OnChangeEvent : public Event
{
private:

public:
	void* ptr_Object; //reference to Object
	Action* MovingUp;
	Action* MovingDown;


public:

	OnChangeEvent()
	{
		MovingUp = new Action();
		MovingDown = new Action();
	}


	~OnChangeEvent()
	{
		delete(MovingUp);
		delete(MovingDown);
	}

};

static bool AEInputKeyChange(const char key, Action* ActionType)
{
	if (AEInputKeyTriggered(key))
	{
		ActionType->IsActionHappening = true;
		return true;

	}
	else if (ActionType->IsActionHappening && !AEInputKeyPressed(key))
	{
		ActionType->IsActionHappening = false;
		return true;
	}
	return false;
}


class UpdateOnEvent : public Event
{
};

class SetLoopFunctionEvent : public Event
{
	Entity *EntityToFollow;
public:

	void SetEntityToFollow(Entity* EntityToFollow) { this->EntityToFollow = EntityToFollow; }
	Entity* getEntityToFollow() { return EntityToFollow; }


};
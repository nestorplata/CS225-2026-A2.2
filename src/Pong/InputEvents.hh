#pragma once
#include<AEEngine.h>
#include "..\Pong\LoopingEventManager.hh"
#include "..\Framework\entity.hh"





//Action Should contain the event
//in this case action represents functionality of bool IsActionHappenning
struct Action
{
	bool IsActionHappening;
};


// OnPlayer InputMovement
class OnSetEvent : public Event
{
private:

public:
	void* ptr_Object; 
	Action* MovingUp;
	Action* MovingDown;


public:

	OnSetEvent()
	{
		MovingUp = new Action();
		MovingDown = new Action();
	}


	~OnSetEvent()
	{
		delete(MovingUp);
		delete(MovingDown);
	}

};

//Empty Event, usuful when desiring to call, a specific object's Method
//Done to be called on update
class UpdateOnEvent : public Event
{
};



//Original Idea was to Have this function call RegisterEventloop. Too tired to implement
// Either to make EventManager inherit from a singleton template class. 
// Or pass EventManager as a pointer on the event. 
// Either way, current assignment 2.2 would stop being about Events
class SetLoopFunctionEvent : public Event
{
	Entity *EntityToFollow;
public:

	void SetEntityToFollow(Entity* EntityToFollow) { this->EntityToFollow = EntityToFollow; }
	Entity* getEntityToFollow() { return EntityToFollow; }


};

//Empty Event, usuful when desiring to call, a specific object's Method
//Done to be called on update
class LoopFunctionEvent : public Event
{

};


//returns true on respective InputChange 
static bool CheckInputKeyChange(const char key, Action* ActionType)
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
#pragma once
#include <algorithm>
#include <vector>
#include <typeinfo>
#include "..\Framework\event_handlers.hh"
#include "..\Framework\event.hh"

//The idea of the following class is to have looping Events.
//Looping events that could be turned on and off
//Input and collision Manager do not differ enough for them to be different classes
//
//Collision Manager Should have been implemented by taking all entities in an entity list.
//such implementation requiered a colliderComponent, Don't wanna do a colliderComponent.

//Input Manager Should have been implemented. No idea on how though


class LoopingEventManager :public EventManager
{
	

private:
	std::vector<Event*> LoopingEvents ;
	void (*Behaviour)(void) = nullptr;
public:
	LoopingEventManager() {};
	~LoopingEventManager() { LoopingEvents.clear(); }
	
	//Sets respecting Manager Behaviours
	bool SetBehaviour(void (*Behaviour)(void))
	{
		return this->Behaviour = Behaviour;
	}
	//Starts Loop Event
	void notifyStartLoopingEvent(Event *event)
	{
		LoopingEvents.push_back(event);
	}

	//Stops Loop Event
	//high chance it simply deletes first event found
	void NotifyEndLoopingEvent(Event* event)
	{
		std::vector<Event*>::iterator it = std::find_if(LoopingEvents.begin(), LoopingEvents.end(),
			[&](Event* other_item)
			{
				//classic Type Id Comparasion
				return typeid(other_item).name() == typeid(event).name();
			});
		if(LoopingEvents.size())LoopingEvents.erase(it);
	}


	//updates EventManager Behaviour
	//Loops through all looping events
	void update() override
	{
		if (Behaviour) Behaviour();
		for (auto events : LoopingEvents)
		{
			notifyEvent(events);
		}
	}

};
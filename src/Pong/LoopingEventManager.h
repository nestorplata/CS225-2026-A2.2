#pragma once
#include <algorithm>
#include <vector>
#include <typeinfo>
#include "..\Framework\event_handlers.hh"
#include "..\Framework\event.hh"

class LoopingEventManager :public EventManager
{
	

private:
	std::vector<Event*> LoopingEvents ;
	void (*Behaviour)(void) = nullptr;
public:
	LoopingEventManager() {};
	//~LoopingEventManager() { LoopingEvents.clear(); }
	
	bool SetBehaviour(void (*Behaviour)(void))
	{
		return this->Behaviour = Behaviour;
	}

	void notifyStartLoopingEvent(Event *event)
	{
		LoopingEvents.push_back(event);
	}


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


	
	void update() override
	{
		if (Behaviour) Behaviour();
		for (auto events : LoopingEvents)
		{
			notifyEvent(events);
		}
	}

};
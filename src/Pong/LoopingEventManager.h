#pragma once
#include "..\Framework\event_handlers.hh"
#include <algorithm>

class LoopingEventManager :public EventManager
{
	

private:
	std::vector<Event*> LoopingEvents;
	void (*Behaviour)(void) = nullptr;
public:
	LoopingEventManager() {};
	~LoopingEventManager() { LoopingEvents.clear(); }
	
	bool SetBehaviour(void (*Behaviour)(void))
	{
		return this->Behaviour = Behaviour;
	}

	void notifyStartLoopingEvent(Event *event)
	{
		LoopingEvents.push_back(event);
	}

	template<typename EVT>
	void NotifyEndLoopingEvent()
	{
		LoopingEvents.erase(std::find_if(LoopingEvents.begin(), LoopingEvents.end(),
			[&](Event* p) { return dynamic_cast<EVT>(p); }));
	}

	
	void update() override
	{
		if (Behaviour) Behaviour();
		for (auto events : LoopingEvents)
		{
			notifyEvent(events);
		}
	};

};
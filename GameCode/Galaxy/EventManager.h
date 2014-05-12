#pragma once
#include "GalaxyDefs.h"
#include <map>
#include <vector>
#include <functional>
#include <list>

class EventData;

class EventManager
{
	typedef std::function<void(EventData*)> EventDelegate;
	typedef std::vector<EventDelegate> EventDelSequence;
	typedef std::map<EventId, EventDelSequence> DelegatesMap;

	typedef std::list<StrongEventPtr> EventSequence;

public:
	EventManager();

	void RegisterDelegate(const EventId& aEventId, EventDelegate aDelegate);

	void DoEvents(unsigned long& aMaxMilliseconds);

	void AddEventToQueue(StrongEventPtr& aEvent);

	void FireEvent(StrongEventPtr& aEvent);

private:
	DelegatesMap mDelegatesMap;

	EventSequence mEventSequence;
};

#pragma once
#include "GalaxyDefs.h"
#include "EventData.h"

class Event
{
public:
	Event(EventData* aEventData) : mEventData(aEventData) {}

	virtual const EventId GetEventId() { assert(0); return ""; }

	EventData* GetData() { return mEventData; }

	~Event() { SAFE_DELETE(mEventData); }

private:
	EventData* mEventData;

};

class ProcessRemovalEvent : public Event
{
public:
	static const EventId sEventId;

	const EventId GetEventId() { return sEventId; }

	ProcessRemovalEvent(EventData* aEventData) : Event(aEventData) {}

};
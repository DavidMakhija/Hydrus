#pragma once
#include "../Galaxy/GalaxyDefs.h"
#include "../Galaxy/Event.h"
#include "../Galaxy/EventData.h"
#include "EventData_Hydrus.h"


class ActorCreatedEvent : public Event
{
public:
	static const EventId sEventId;

	const EventId GetEventId() { return sEventId; }

	ActorCreatedEvent(EventData_ActorCreated* aEventData) : Event(aEventData) {}

};

class ActorReadyEvent : public Event
{
public:
	static const EventId sEventId;

	const EventId GetEventId() { return sEventId; }

	ActorReadyEvent(EventData_ActorReady* aEventData) : Event(aEventData) {}

};

class TargetingEvent : public Event
{
public:
	static const EventId sEventId;

	const EventId GetEventId() { return sEventId; }

	TargetingEvent(EventData_Targeting* aEventData) : Event(aEventData) {}

};


class ActorMinHealthEvent : public Event
{
public:
	static const EventId sEventId;

	const EventId GetEventId() { return sEventId; }

	ActorMinHealthEvent(EventData_ActorMinHealth* aEventData) : Event(aEventData) {}

};



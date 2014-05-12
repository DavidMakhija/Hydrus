#include "EventManager.h"
#include "../Galaxy/GalaxyAlgorithms.h"
#include <algorithm>
#include <cassert>
#include "Event.h"
#include "FactoryHelper.h"

GenericObjectFactory<Event,EventId>* p_gEventFactory = nullptr;

EventManager::EventManager()
{
	p_gEventFactory = new GenericObjectFactory<Event, EventId>();
}

void EventManager::RegisterDelegate(const EventId& aEventId, EventDelegate aDelegate)
{
	EventDelSequence& eventDelegates = mDelegatesMap[aEventId];

	auto jt = std::find_if(eventDelegates.begin(), eventDelegates.end(), [&](EventDelegate delegateIt) 
	{
		void(*const* ptr1)(int) = aDelegate.target<void(*)(int)>();
		void(*const* ptr2)(int) = delegateIt.target<void(*)(int)>();
		if (ptr1 && ptr2 && *ptr1 == *ptr2)
		{
			return true;
		}
		return false;
	});

	if (jt != eventDelegates.end())
	{
		assert(0); // Event already registered this delegate
	}

	eventDelegates.push_back(aDelegate);

}

void EventManager::DoEvents(unsigned long& aMaxMilliseconds)
{
	clock_t startTime = clock();
	clock_t currentTime = clock();
	long timeRemaining = GalaxyAlgorithms::TimeRemaining(aMaxMilliseconds, startTime, currentTime);

	while ((timeRemaining > 0) && (!mEventSequence.empty()))
	{
		this->FireEvent(mEventSequence.front());
		mEventSequence.pop_front();

		currentTime = clock();
	}

}

void EventManager::AddEventToQueue(StrongEventPtr& aEvent)
{
	mEventSequence.push_back(aEvent);

}

void EventManager::FireEvent(StrongEventPtr& aEvent)
{
	EventId id = aEvent->GetEventId();

	EventDelSequence& delegateSeq = mDelegatesMap[id];

	for (auto& i : delegateSeq)
	{
		EventData* data = aEvent->GetData();
		i(data);
	}

}
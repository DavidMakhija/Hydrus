#include "GalaxyDefs.h"
#include <list>

typedef std::list<int> EventSequence;

class EventManager
{
public:
	EventSequence mEventSeq;

	void CreateEvent(StrongEventPtr aEvent);

	virtual void EventFire();


private:
	EventManager() { assert(0); }
	~EventManager() {}
	EventManager(const EventManager&) { assert(0); }
	EventManager operator=(const EventManager& ){ assert(0); }

};
#include "../Galaxy/ConsoleView.h"
class EventData;


class HydrusConsoleView : public ConsoleView
{
public:
	HydrusConsoleView();

	void ActorReadyDelegate(EventData* aEventData);
	void TargetingDelegate(EventData* aEventData);

private:

};


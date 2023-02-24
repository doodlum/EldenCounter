#include "include/Hooks.h"
#include "include/guardCounter.h"

void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSE::MessagingInterface::kDataLoaded:
		guardCounter::GetSingleton()->loadData();
		guardCounter::GetSingleton()->readSettings();
	}
}

void Load()
{	
	SKSE::GetMessagingInterface()->RegisterListener("SKSE", MessageHandler);
	Hooks::install();
}

#pragma once
#include "stdafx.h"
#include <string>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <memory>
#include <algorithm>

typedef double        Real;
typedef int           Int;
typedef unsigned int  UInt;

typedef unsigned int  ActorId;
typedef std::string ComponentId;

class Actor;
typedef std::shared_ptr<Actor> StrongActorPtr;
typedef std::weak_ptr<Actor>   WeakActorPtr;

class Process;
typedef std::shared_ptr<Process> StrongProcessPtr;
typedef std::weak_ptr<Process>   WeakProcessPtr;

class Event;
typedef std::shared_ptr<Event> StrongEventPtr;
typedef std::weak_ptr<Event>   WeakEventPtr;


// (Stolen from) Game Code Complete - Chapter 12, page 446-447
#if defined(_DEBUG)
#	define GALAXY_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)
#else
#	define GALAXY_NEW new
#endif

// A useful macro
#define SAFE_DELETE(p) { if (p) { delete (p); (p)=NULL; } }

template<typename PointerType>
std::shared_ptr<PointerType> MakeStrongPointer(std::weak_ptr<PointerType> aPointer)
{
	if (aPointer.expired() == true)
	{
		return std::shared_ptr<PointerType>();
	}
	else
	{
		return std::shared_ptr<PointerType>(aPointer);
	}
}

#define GET_COMPONENT(type) GetComponent<type>(type::GetComponentString())

enum ActionType
{
	ATTACK,
	PASS
};
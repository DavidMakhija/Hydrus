#pragma once
#include "../Galaxy/GalaxyDefs.h"

template <class Baseclass, class Subclass>
Baseclass* GenericObjectCreationFunction(void) { return GALAXY_NEW Subclass; }

template<typename Baseclass, typename IdType>
class GenericObjectFactory
{
	typedef Baseclass* (*ObjectCreationFunction) (void);
	std::map<IdType,ObjectCreationFunction> mFunctionCreationMap;

public:
	template<typename Subclass>
	static void AddClassToFactory(IdType aType)
	{
		auto it = mFunctionCreationMap.find(aType);
		if (it != mFunctionCreationMap.end())
		{
			assert(0); // Map already contains this class
		}
		else
		{
			mFunctionCreationMap[aType] = &GenericObjectCreationFunction<BaseClass, SubClass>;
		}
	}

};

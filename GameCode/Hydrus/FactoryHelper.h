#pragma once
#include "../Galaxy/GalaxyDefs.h"

template <class Baseclass, class Subclass>
Baseclass* GenericObjectCreationFunction(void) { return new Subclass; }

template<typename Baseclass, typename IdType>
class GenericObjectFactory
{
	typedef Baseclass* (*ObjectCreationFunction) (void);
	std::map<IdType,ObjectCreationFunction> mFunctionCreationMap;
public:
	static void AddClassToFactory(IdType aType);
};

template<typename Subclass>
void GenericObjectFactory<Baseclass,IdType>::AddClassToFactory(IdType aType)
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
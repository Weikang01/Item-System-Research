#pragma once
#include "pch.h"

using ComponentTypeID	= std::size_t;
using EntityID			= std::size_t;

inline ComponentTypeID getComponentID()
{
	static ComponentTypeID basicID = 0;
	return basicID++;
}

template<typename T>
ComponentTypeID getComponentID()
{
	static ComponentTypeID basicID = getComponentID();
	return basicID;
}

constexpr unsigned int MAX_COMPONENT = 32;

template<typename T>
std::vector<std::pair<T, EntityID>>* getComponentVector()
{
	static std::vector<std::pair<T, EntityID>>* components = new std::vector<std::pair<T, EntityID>>{};
	return components;
}


class Registry
{
	using componentBitset = std::bitset<MAX_COMPONENT>;
	using componentBitsets = std::vector<std::bitset<MAX_COMPONENT>>;

	using componentArray = std::array<void*, MAX_COMPONENT>;
	using componentArrays = std::vector<std::array<void*, MAX_COMPONENT>>;

	componentBitsets entities_bitsets;
	componentArrays entities_components;

public:
	EntityID createEntity()
	{
		static EntityID basicID = 0;
		entities_bitsets.emplace_back(componentBitset());
		entities_components.emplace_back(componentArray());
		return basicID++;
	}

	template<typename T, typename... TArgs>
	T* addComponent(EntityID entt, TArgs&&... args)
	{
		entities_bitsets[entt].set(getComponentID<T>(), true);
		getComponentVector<T>()->emplace_back(T(std::forward(args)...), entt);
		T* c(&(getComponentVector<T>()->back().first));

		entities_components[entt][getComponentID<T>()] = (void*)c;

		return c;
	}

	template<typename T>
	bool hasComponent(EntityID entt)
	{
		return entities_bitsets[entt].test(getComponentID<T>());
	}

	template<typename T>
	T* getComponent(EntityID entt)
	{
		return static_cast<T*>(entities_components[entt][getComponentID<T>()]);
	}

	template<typename T>
	std::vector<std::pair<T, EntityID>>* getComponents()
	{
		return getComponentVector<T>();
	}
};
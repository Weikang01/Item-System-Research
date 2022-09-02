#pragma once
#include "pch.h"

using ComponentTypeID	= std::size_t;
using ComponentID		= std::size_t;
using EntityID			= std::size_t;

inline ComponentTypeID getComponentTypeID()
{
	static ComponentTypeID basicID = 0;
	return basicID++;
}

template<typename T>
ComponentTypeID getComponentTypeID()
{
	static ComponentTypeID basicID = getComponentTypeID();
	return basicID;
}

constexpr unsigned int MAX_COMPONENT = 128;

template<typename T>
std::vector<std::pair<T, EntityID>>* getComponentVector()
{
	static std::vector<std::pair<T, EntityID>>* componentVector = new std::vector<std::pair<T, EntityID>>{};
	return componentVector;
}

template<typename T>
void deleteFromComponentVector(ComponentID componentID)
{
	static std::vector<ComponentID> deletedComponents{};
}


class Registry
{
	template<typename T>
	struct ComponentVector
	{
	private:
		ComponentVector<T>() {}
		
		const EntityID DELETE_ENTT_GUARDIAN = (~(EntityID)0);
		std::vector<ComponentID> deletedComponents{};
		
	public:
		using componentEntityPair = std::pair<EntityID, T>;
		std::vector<componentEntityPair> components{};

		ComponentVector<T>(ComponentVector<T> const&) = delete;
		void operator=(ComponentVector<T> const&) = delete;

		static ComponentVector<T>& getInstance()
		{
			static ComponentVector<T> inst = ComponentVector<T>{};
			return inst;
		}

		T& getComponent(const ComponentID componentID)
		{
			if (components.size() > componentID && components[componentID].first != DELETE_ENTT_GUARDIAN)
				return components[componentID].second;
			assert(0, "The component has been deleted");
		}

		void deleteComponent(const ComponentID& componentID)
		{
			if (components.size() > componentID && components[componentID].first != DELETE_ENTT_GUARDIAN)
			{
				deletedComponents.emplace_back(std::move(componentID));
				components[componentID].first = DELETE_ENTT_GUARDIAN;
			}
		}

		template<typename... _Valty>
		ComponentID emplace_back(EntityID entt, _Valty&&... vals)
		{
			if (deletedComponents.empty())
			{
				components.emplace_back(entt, std::move(T((vals)...)));
				return components.size() - 1;
			}
			else
			{
				ComponentID cid = deletedComponents.back();
				deletedComponents.pop_back();
				components[cid] = componentEntityPair(entt, std::move(T((vals)...)));
				return cid;
			}
		}
	};

	using entityBitset = std::bitset<MAX_COMPONENT>;
	using entityBitsets = std::vector<entityBitset>;

	using entityComponentsArray = std::array<ComponentID, MAX_COMPONENT>;
	using entityComponentsArrays = std::vector<entityComponentsArray>;

	entityBitsets entities_bitsets;
	entityComponentsArrays entities_components;

public:

	EntityID createEntity()
	{
		static EntityID basicID = 0;
		entities_bitsets.emplace_back(entityBitset());
		entities_components.emplace_back(entityComponentsArray());
		return basicID++;
	}

	template<typename T, typename... TArgs>
	T& addComponent(EntityID entt, TArgs&&... args)
	{
		entities_bitsets[entt].set(getComponentTypeID<T>(), true);
		
		ComponentID cid = ComponentVector<T>::getInstance().emplace_back(entt, std::forward<TArgs>(args)...);
		entities_components[entt][getComponentTypeID<T>()] = cid;

		return (ComponentVector<T>::getInstance().getComponent(cid));
	}

	template<typename T>
	bool hasComponent(EntityID entt)
	{
		return entities_bitsets[entt].test(getComponentTypeID<T>());
	}

	template<typename T>
	T& getComponent(EntityID entt)
	{
		return ComponentVector<T>::getInstance().getComponent(entities_components[entt][getComponentTypeID<T>()]);
	}

	template<typename T>
	void deleteComponent(EntityID entt)
	{
		entities_bitsets[entt].reset(entt);
		ComponentVector<T>::getInstance().deleteComponent(entities_components[entt][getComponentTypeID<T>()]);
	}

	template<typename T>
	std::vector<std::pair<T, EntityID>>* getComponents()
	{
		return getComponentVector<T>();
	}
};
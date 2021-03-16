#pragma once

//templates/r136.h

#include "types/r136.h"
#include <stdexcept>

template <class E>
constexpr auto to_value(E e) noexcept
{
	return static_cast<std::underlying_type_t<E>>(e);
}

template<class L>
constexpr L combines_with(L value) { return -(value + 2); }

constexpr AnimateID combines_with(ItemID item) { return static_cast<AnimateID>(combines_with(to_value(item))); }
constexpr ItemID combines_with(AnimateID animate) { return static_cast<ItemID>(combines_with(to_value(animate))); }

template<class TEntity >
BoundedCollection<TEntity>::BoundedCollection(int capacity) :
	max_item_count(capacity)
{}

template<class TEntity>
bool BoundedCollection<TEntity>::is_full() const
{
	return items.size() >= max_item_count;
}

template<class TEntity>
bool BoundedCollection<TEntity>::contains(TEntity item) const
{
	for (auto& element : items)
		if (element == item)
			return true;

	return false;
}

template<class TEntity>
bool BoundedCollection<TEntity>::add(TEntity item)
{
	if (is_full())
		return false;

	items.push_back(item);
	return true;
}

template<class TEntity>
bool BoundedCollection<TEntity>::remove(TEntity item)
{
	for (auto element = items.begin(); element != items.end(); ++element)
	{
		if (*element == item)
		{
			items.erase(element);
			return true;
		}
	}

	return false;
}

template<class TEntity>
size_t BoundedCollection<TEntity>::count() const
{
	return items.size();
}

template<class TEntity>
typename std::vector<TEntity>::iterator BoundedCollection<TEntity>::begin()
{
	return items.begin();
}

template<class TEntity>
typename std::vector<TEntity>::iterator BoundedCollection<TEntity>::end()
{
	return items.end();
}

template<class TKey, class TValue>
inline EntityMap<TKey, TValue>::EntityMap(bool delete_values) :
	delete_values(delete_values)
{}

template<class TKey, class TValue>
inline EntityMap<TKey, TValue>::~EntityMap()
{
	if (!delete_values)
		return;

	for (auto element = map.begin(); element != map.end();)
	{
		delete element->second;
		element = map.erase(element);
	}
}

template<class TKey, class TValue>
void EntityMap<TKey, TValue>::add_or_set(TValue& value)
{
	auto key = value.id;
	auto element = map.find(key);
	if (element == map.end())
		map.insert(std::make_pair(key, &value));
	else
		element->second = &value;
}

template<class TKey, class TValue>
void EntityMap<TKey, TValue>::add_or_set(TValue* value)
{
	auto key = value->id;
	auto element = map.find(key);
	if (element == map.end())
		map.insert(std::make_pair(key, value));
	else
		element->second = value;
}

template<class TKey, class TValue>
bool EntityMap<TKey, TValue>::contains(TKey key)
{
	return map.find(key) != map.end();
}

template<class TKey, class TValue>
TValue& EntityMap<TKey, TValue>::operator[](TKey key)
{
	auto element = map.find(key);
	if (element == map.end())
		throw std::out_of_range("key");

	return *(element->second);
}

template<class TKey, class TValue>
typename std::map<TKey, TValue*>::iterator EntityMap<TKey, TValue>::begin()
{
	return map.begin();
}

template<class TKey, class TValue>
typename std::map<TKey, TValue*>::iterator EntityMap<TKey, TValue>::end()
{
	return map.end();
}

template<class TKey, class TValue>
void EntityMap<TKey, TValue>::clear()
{
	map.clear();
}
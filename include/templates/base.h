#pragma once

//templates/base.h

#include "types/base.h"
#include <stdexcept>

template<class TEntity>
BoundedCollection<TEntity>::BoundedCollection(int capacity) :
	max_item_count(capacity)
{}

template<class TEntity>
bool BoundedCollection<TEntity>::is_full() const
{
	return items.size() >= (unsigned)max_item_count;
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
void EntityMap<TKey, TValue>::add_or_set(std::unique_ptr<TValue> value)
{
	auto key = value->id;
	auto element = map.find(key);
	if (element == map.end())
		map.insert(std::make_pair(key, std::move(value)));
	else
		element->second.reset(value.get());
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
typename std::map<TKey, std::unique_ptr<TValue>>::iterator EntityMap<TKey, TValue>::begin()
{
	return map.begin();
}

template<class TKey, class TValue>
typename std::map<TKey, std::unique_ptr<TValue>>::iterator EntityMap<TKey, TValue>::end()
{
	return map.end();
}

template<class TKey, class TValue>
void EntityMap<TKey, TValue>::clear()
{
	map.clear();
}
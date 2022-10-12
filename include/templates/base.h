#pragma once

//templates/base.h

#include "types/base.h"
#include <cstdarg>
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

template<class TParam>
constexpr TParam select_language_param(Language language, TParam first_param...)
{
	auto param_index = to_value(language);
	if (param_index == 0)
		return first_param;

	constexpr auto language_count = to_value(Language::COUNT);
	std::va_list params;
	TParam selected_param = TParam();

	va_start(params, first_param);
	for (int i = 1; i <= param_index && i < language_count; i++)
		selected_param = va_arg(params, TParam);

	va_end(params);

	return selected_param;
}

template<class TChar>
const std::basic_string<TChar> empty_string = std::basic_string<TChar>();

template<class TChar>
const std::basic_string<TChar> &select_language_param(Language language, const std::vector<std::basic_string<TChar>>& texts)
{
	auto language_value = to_value(language);
	return texts.size() > language_value ? texts[language_value] : empty_string<TChar>;
}

template<class TArrayType>
const TArrayType& select_language_param(Language language, const TArrayType* values)
{
	return values[to_value(language)];
}
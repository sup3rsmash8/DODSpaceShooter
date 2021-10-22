#pragma once

#include <vector>
#include <map>

/// <summary>
/// Erases an object from a vector, if it exists in it.
/// Returns whether or not it was successfully erased
/// (i.e. returns false if it couldn't be found in the vector).
/// </summary>
template<class T>
bool EraseObjectFromVector(std::vector<T>& vector, T vectorObject)
{
	if (!vectorObject)
		return false;

	for (size_t i = 0, ilen = vector.size(); i < ilen; ++i)
	{
		if (vector[i] == vectorObject)
		{
			vector.erase(vector.begin() + i);
			return true;
		}
	}

	return false;
}

/// <summary>
/// Returns whether a vector contains an object or not.
/// </summary>
template<class T>
bool VectorContains(std::vector<T>& vector, T vectorObject)
{
	for (size_t i = 0, ilen = vector.size(); i < ilen; ++i)
	{
		if (vector[i] == vectorObject)
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// Returns whether or not a vector contains an object with the same address as vectorObject.
/// </summary>
template<class T>
bool VectorContains_Addr(std::vector<T>& vector, T vectorObject)
{
	for (size_t i = 0, ilen = vector.size(); i < ilen; ++i)
	{
		if (&vector[i] == &vectorObject)
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// Tests a map of similar types to see if it contains object1 as 
/// a key and object2 as a value and vice versa.
/// </summary>
template<class T>
bool MapContainsAsKeyOrValue(std::map<T, T>& map, T object1, T object2)
{
	if (map.find(object1) != map.end())
	{
		if (map[object1] == object2)
			return true;
	}
	else if (map.find(object2) != map.end())
	{
		if (map[object2] == object1)
			return true;
	}

	return false;
}
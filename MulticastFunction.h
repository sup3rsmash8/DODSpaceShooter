#pragma once
#include <vector>
#include <functional>
#include "VectorExtensions.h"
#include "TupleUnpackers.h"



template<class... T>
struct MulticastFunction
{
	//~MulticastFunction();

private:
	std::vector<std::function<void(T...)>*> m_functionCollection = std::vector<std::function<void(T...)>*>();

public:
	void Subscribe(std::function<void(T...)>* function);
	void Unsubscribe(std::function<void(T...)>* function);

	//void operator()(T... args);
	void Call(const std::tuple<T...>& params);

private:
	template<typename P, int... S>
	void Call_Internal(const P& params, const seq<S...>);
};

template<class... T>
inline void MulticastFunction<T...>::Subscribe(std::function<void(T...)>* function)
{
	if (!VectorContains_Addr(m_functionCollection, function))
	{
		m_functionCollection.push_back(function);
	}
}

template<class... T>
inline void MulticastFunction<T...>::Unsubscribe(std::function<void(T...)>* function)
{
	bool hasErased = false;

	for (size_t i = 0, ilen = m_functionCollection.size(); i < ilen; ++i)
	{
		if (i >= m_functionCollection.size())
			break;

		if (m_functionCollection[i] == function)
		{
			m_functionCollection.erase(m_functionCollection.begin() + i);
			hasErased = true;
		}
	}

	//if (hasErased)
	//	printf("Erase successful\n");
	//else
	//	printf("Erase failure\n");
}

template<class... T>
inline void MulticastFunction<T...>::Call(const std::tuple<T...>& params)
{
	Call_Internal(params, typename gens<sizeof...(T)>::type());
}

template<class... T>
template<typename P, int... S>
inline void MulticastFunction<T...>::Call_Internal(const P& params, const seq<S...>)
{
	for (size_t i = 0, ilen = m_functionCollection.size(); i < ilen; ++i)
	{
		if (m_functionCollection[i])
		{
			(*m_functionCollection[i])(std::get<S>(params)...);
		}
	}
}
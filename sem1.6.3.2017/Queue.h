#pragma once

#include "Structure.h"

namespace DS
{
	template<typename T>
	class Queue :
		public Structure
	{
	public:
		virtual ~Queue();

		virtual Queue<T>& operator=(const Queue<T>& other) = 0;

		virtual size_t size() const = 0;
		virtual bool isEmpty() const = 0;
		virtual void clear() = 0;

		virtual void push(const T& data) = 0;
		virtual T pop() = 0;
		virtual T& peek() = 0;
		virtual const T& peek() const = 0;
	protected:
		Queue();
	};

	template<typename T>
	Queue<T>::~Queue()
	{
	}
	template<typename T>
	Queue<T>::Queue() :
		Structure()
	{
	}
}

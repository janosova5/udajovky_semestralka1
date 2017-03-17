#pragma once

#include "Structure.h"

namespace DS {

	template<typename T>
	class PriorityQueue :
		public Structure
	{
	public:
		virtual ~PriorityQueue();

		virtual Structure* clone() const = 0;
		virtual Structure& operator=(const Structure& other) = 0;
		virtual PriorityQueue<T>& operator=(const PriorityQueue<T>& other) = 0;

		virtual size_t size() const = 0;
		virtual bool isEmpty() const = 0;
		virtual void clear() = 0;

		virtual void push(const int priority, const T& data) = 0;
		virtual void push(const double priority, const T& data) = 0;
		virtual T pop() = 0;
		virtual T& peek() = 0;
		virtual const T& peek() const = 0;
		//virtual const T& peek(int index) = 0;
		virtual int peekPriority() const = 0;
	protected:
		PriorityQueue();
	};

	template<typename T>
	PriorityQueue<T>::~PriorityQueue()
	{
	}

	template<typename T>
	PriorityQueue<T>::PriorityQueue() :
		Structure()
	{
	}

}


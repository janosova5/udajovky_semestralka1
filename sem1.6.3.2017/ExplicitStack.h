#pragma once

#include "Stack.h"

namespace DS
{
	template<typename T>
	class ExplicitStack :
		public Stack<T>
	{
	public:
		ExplicitStack();
		ExplicitStack(const ExplicitStack<T>& other);
		~ExplicitStack() override;

		Structure* clone() const override;
		ExplicitStack<T>& operator=(const ExplicitStack<T>& other);

		void push(const T& data) override;
	protected:
		int indexOfPeek() const override;
	};

	template<typename T>
	ExplicitStack<T>::ExplicitStack() : Stack<T>(LinkedList<T>())
	{

	}

	template<typename T>
	ExplicitStack<T>::ExplicitStack(const ExplicitStack<T>& other) : Stack<T>(LinkedList<T>())
	{

	}

	template<typename T>
	ExplicitStack<T>::~ExplicitStack()
	{
	}

	template<typename T>
	Structure* ExplicitStack<T>::clone() const
	{
		return new ExplicitStack<T>(*this);
	}

	template<typename T>
	ExplicitStack<T>& ExplicitStack<T>::operator=(const ExplicitStack<T>& other)
	{
		returnn Stack<T>::operator=(other);
	}

	template<typename T>
	void ExplicitStack<T>::push(const T& data)
	{
		list_->add(data);
	}

	template<typename T>
	inline int ExplicitStack<T>::indexOfPeek() const
	{
		return static_cast<int> (list_->size()) - 1;
	}
}

#pragma once

#include "Structure.h"
#include "List.h"
#include "LinkedList.h"
#include "ArrayList.h"


namespace DS
{
	template<typename T>
	class Stack :
		public Structure
	{
	public:
		virtual ~Stack();

		virtual Structure* clone() const = 0;
		Structure& operator=(const Structure& other) override;
		virtual Stack<T>& operator=(const Stack<T>& other);

		virtual size_t size() const;
		virtual bool isEmpty() const;
		virtual void clear();

		virtual void push(const T& data) = 0;
		virtual T pop();
		virtual T& peek();
		virtual const T& peek() const;
	protected:
		List<T>* list_;

		Stack(const List<T>& list);
		Stack(const Stack<T>& other);

		virtual int indexOfPeek() const = 0;
	};

	template<typename T>
	Stack<T>::Stack(const List<T>& list) : list_(dynamic_cast<List<T>*>(list.clone()))
	{

	}

	template<typename T>
	Stack<T>::Stack(const Stack<T>& other) : list_(dynamic_cast<List<T>*>(other.list->clone()))
	{

	}

	template<typename T>
	Stack<T>::~Stack()
	{
		delete list_;
		list_ = nullptr;
	}

	template<typename T>
	Structure& Stack<T>::operator=(const Structure& other)
	{
		*this = dynamic_cast<const Stack<T>&>(other);
		return *this;
	}

	template<typename T>
	Stack<T>& Stack<T>::operator=(const Stack<T>& other)
	{
		if (this != &other)
		{
			*list_ = *other.list_;

		}


		return *this;


	}

	template<typename T>
	size_t Stack<T>::size() const
	{
		return list_->size();
	}

	template<typename T>
	bool Stack<T>::isEmpty() const
	{
		return size() <= 0;
	}

	template<typename T>
	void Stack<T>::clear()
	{
		list_->clear();
	}

	template<typename T>
	T Stack<T>::pop()
	{
		return list_->removeAt(indexOfPeek());
	}

	template<typename T>
	T& Stack<T>::peek()
	{
		return (*list_)[indexOfPeek()];
	}

	template<typename T>
	const T& Stack<T>::peek() const
	{
		return (*list_)[indexOfPeek()];
	}

}

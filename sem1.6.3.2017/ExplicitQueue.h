#pragma once

#include "Queue.h"
#include "LinkedList.h"

namespace DS
{
	template<typename T>
	class ExplicitQueue :
		public Queue<T>
	{
	public:
		ExplicitQueue();
		ExplicitQueue(const ExplicitQueue<T>& other);

		~ExplicitQueue() override;

		Structure* clone() const override;

		Structure& operator=(const Structure& other) override;
		Queue<T>& operator=(const Queue<T>& other) override;
		ExplicitQueue<T>& operator=(const ExplicitQueue<T>& other);

		size_t size() const override;
		bool isEmpty() const override;
		void clear() override;

		void push(const T& data) override;
		T pop() override;
		T& peek() override;
		const T& peek() const override;
	private:
		LinkedList<T>* list_;
		size_t size_;
	};

	template<typename T>
	ExplicitQueue<T>::ExplicitQueue() : size_(0), list_(new LinkedList<T>)
	{

	}

	template<typename T>
	ExplicitQueue<T>::ExplicitQueue(const ExplicitQueue<T>& other) : list_(new LinkedList<T>(*other.list_)), size_(other.size_)

	{

	}

	template<typename T>
	ExplicitQueue<T>::~ExplicitQueue()
	{
		delete list_;
		size_ = 0;
	}

	template<typename T>
	Structure * ExplicitQueue<T>::clone() const
	{
		return new ExplicitQueue<T>(*this);
	}

	template<typename T>
	Structure& ExplicitQueue<T>::operator=(const Structure& other)
	{
		*this = dynamic_cast< ExplicitQueue<T>&>(other);
		return *this;
	}

	template<typename T>
	Queue<T>& ExplicitQueue<T>::operator=(const Queue<T>& other)
	{
		*this = dynamic_cast< ExplicitQueue<T>&>(other);
		return *this;
	}

	template<typename T>
	ExplicitQueue<T>& ExplicitQueue<T>::operator=(const ExplicitQueue<T>& other)
	{
		if (this != &other) {
			list_ = other.list_;

		}
		return *this;
	}

	template<typename T>
	size_t ExplicitQueue<T>::size() const
	{
		return size_;
	}

	template<typename T>
	bool ExplicitQueue<T>::isEmpty() const
	{
		return (size <= 0);
	}

	template<typename T>
	void ExplicitQueue<T>::clear()
	{
		list_->clear();
		size_ = 0;
	}

	template<typename T>
	void ExplicitQueue<T>::push(const T & data)
	{
		list_->add(data);
		size_++;
	}

	template<typename T>
	T ExplicitQueue<T>::pop()
	{


		size_--;
		return list_->removeAt(0);
	}

	template<typename T>
	T& ExplicitQueue<T>::peek()
	{
		return (*list_)[0]->getData();
	}

	template<typename T>
	const T& ExplicitQueue<T>::peek() const
	{
		return (*list_)[0]->getData();
	}
}

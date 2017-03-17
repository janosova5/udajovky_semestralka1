#pragma once

#include "Queue.h"
#include "Array.h"
#include <stdexcept>

namespace DS
{
	template<typename T>
	class ImplicitQueue :
		public Queue<T>
	{
	public:
		ImplicitQueue(const size_t capacity);
		ImplicitQueue(const ImplicitQueue<T>& other);

		~ImplicitQueue() override;

		Structure* clone() const override;

		Structure& operator=(const Structure& other) override;
		Queue<T>& operator=(const Queue<T>& other) override;
		ImplicitQueue<T>& operator=(const ImplicitQueue<T>& other);

		size_t size() const override;
		bool isEmpty() const override;
		void clear() override;

		void push(const T& data) override;
		T pop() override;
		T& peek() override;
		const T& peek() const override;
	private:
		Array<T>* array_;
		int startIndex;
		size_t size_;
	};

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue(const size_t capacity) : array_(new Array<T>(capacity)), startIndex(0), size_(0)
	{

	}

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue(const ImplicitQueue<T>& other) : array_(new Array<T>(*other.array_)), startIndex(other.startIndex), size_(other.size_)
	{

	}

	template<typename T>
	ImplicitQueue<T>::~ImplicitQueue()
	{
		delete array_;
	}

	template<typename T>
	Structure * ImplicitQueue<T>::clone() const
	{
		return new ImplicitQueue<T>(*this);
	}
	template<typename T>
	Structure& ImplicitQueue<T>::operator=(const Structure& other)
	{
		*this = dynamic_cast< ImplicitQueue<T>&>(other);
		return *this;
	}

	template<typename T>
	Queue<T>& ImplicitQueue<T>::operator=(const Queue<T>& other)
	{
		*this = dynamic_cast< ImplicitQueue<T>&>(other);
		return *this;
	}

	template<typename T>
	ImplicitQueue<T>& ImplicitQueue<T>::operator=(const ImplicitQueue<T>& other)
	{
		if (this != &other) {
			*array_ = *other.array_;
			startIndex = other.startIndex;
			size_ = other.size_;

		}
		return *this;
	}

	template<typename T>
	size_t ImplicitQueue<T>::size() const
	{
		return size_;
	}

	template<typename T>
	bool ImplicitQueue<T>::isEmpty() const
	{
		return size() <= 0;
	}

	template<typename T>
	void ImplicitQueue<T>::clear()
	{
		startIndex = 0;
		size_ = 0;
	}

	template<typename T>
	void ImplicitQueue<T>::push(const T & data)
	{
		if (size_ == array_->size()) {

			throw::std::length_error("Queue is full");
		}

		(*array_)[(startIndex + static_cast<int>(size_)) % static_cast<int>(array_->size())] = data;

		size_++;
	}

	template<typename T>
	T ImplicitQueue<T>::pop()
	{
		if (size_ == 0) {

			throw::std::length_error("Queue is empty");
		}
		T pom = (*array_)[startIndex];
		startIndex = (startIndex + 1) % static_cast<int>(array_->size());
		return pom;
	}

	template<typename T>
	T& ImplicitQueue<T>::peek()
	{
		if (size_ == 0) {

			throw::std::length_error("Queue is empty");
		}
		return (*array_)[startIndex];
	}

	template<typename T>
	const T& ImplicitQueue<T>::peek() const
	{
		if (size_ == 0) {

			throw::std::length_error("Queue is empty");
		}
		return (*array_)[startIndex];
	}
}

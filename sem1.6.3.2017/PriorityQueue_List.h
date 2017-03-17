#pragma once

#include "PriorityQueue.h"
#include "StructureItem.h"

namespace DS {
	template<typename T>
	class PriorityQueue_List :
		public PriorityQueue<T>
	{
	public:
		virtual ~PriorityQueue_List();

		Structure& operator=(const Structure& other) override;
		PriorityQueue<T>& operator=(const PriorityQueue<T>& other) override;
		PriorityQueue_List<T>& operator=(const PriorityQueue_List<T>& other);

		size_t size() const override;
		bool isEmpty() const override;
		void clear() override;

		T& peek() override;
		const T& peek() const override;
		const T& peek(int index) const;
		int peekPriority() const override;
	protected:
		List<PriorityItem<T>*> *list_;
		//List<PriorityItem1<T>*> *list_;
		PriorityQueue_List(List<PriorityItem<T>*>* list);
		virtual int indexOfHighestPriority() const;
	};

	template<typename T>
	PriorityQueue_List<T>::PriorityQueue_List(List<PriorityItem<T>*>* list) : list_(list)
	{

	}

	template<typename T>
	PriorityQueue_List<T>::~PriorityQueue_List()
	{
		clear();
		delete list_;
		list_ = nullptr;
	}

	template<typename T>
	Structure& PriorityQueue_List<T>::operator=(const Structure& other)
	{
		*this = dynamic_cast<const  PriorityQueue_List<T>&>(other);
		return *this;
	}

	template<typename T>
	PriorityQueue<T>& PriorityQueue_List<T>::operator=(const PriorityQueue<T>& other)

	{
		*this = dynamic_cast<const  PriorityQueue_List<T>&>(other);
		return *this;
	}

	template<typename T>
	PriorityQueue_List<T>& PriorityQueue_List<T>::operator=(const PriorityQueue_List<T>& other)
	{
		clear();

		if (this != &other) {
			if (typeid(*this) != typeid(other)) { //treba ziskat priamo objekt
				throw std::invalid_argument("Bad assigment");
			}
			for (PriorityItem<T>* pom : *other.list_) { //foreach
				list_->add(new PriorityItem<T>(*pom));
			}

		}
		return *this;
	}

	template<typename T>
	size_t PriorityQueue_List<T>::size() const
	{
		return list_->size();
	}

	template<typename T>
	bool PriorityQueue_List<T>::isEmpty() const
	{
		return size() <= 0;
	}

	template<typename T>
	inline void PriorityQueue_List<T>::clear()
	{

		for (PriorityItem<T>* pom : *list_) {
			delete pom;
		}
		list_->clear();

	}
	template<typename T>
	inline int PriorityQueue_List<T>::indexOfHighestPriority() const
	{
		int priority = (*list_)[0]->getPriority();
		int index = 0;
		int i = 0;
		for (PriorityItem<T>* pom : *list_) {
			if (priority < pom->getPriority()) {
				priority = pom->getPriority();
				index = i;
			}
			i++;
		}
		return index;

	}

	template<typename T>
	inline T & PriorityQueue_List<T>::peek()
	{
		return 	(*list_)[indexOfHighestPriority()]->getData();
	}

	template<typename T>
	inline const T & PriorityQueue_List<T>::peek() const
	{
		return (*list_)[indexOfHighestPriority()]->getData();
	}

	template<typename T>
	inline const T & PriorityQueue_List<T>::peek(int index) const
	{
		return (*list_)[index]->getData();
	}

	template<typename T>
	inline int PriorityQueue_List<T>::peekPriority() const
	{
		return (*list_)[indexOfHighestPriority()]->getPriority();
	}

}

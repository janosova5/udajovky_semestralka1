#pragma once

#include "List.h"
#include "StructureItem.h"

namespace DS
{
	template<typename T>
	class LinkedList :
		public List<T>
	{
	protected:
		class LinkedListIterator :
			public StructureIterator<T>
		{
		public:
			LinkedListIterator(const LinkedItem<T>* item);

			bool operator!=(const StructureIterator<T>& other) const override;
			const T& operator*() const override;
			const StructureIterator<T>& operator++() override;

			StructureIterator<T>* clone() const override;
		private:
			// atributy
			const LinkedItem<T>* aItem;

		};

	public:
		LinkedList(const EqualityFunction<T>& equalityFunction = functionEqual);
		LinkedList(const LinkedList<T>& other);
		~LinkedList() override;

		Structure* clone() const override;
		Structure& operator=(const Structure& other) override;
		List<T>& operator=(const List<T>& other) override;
		LinkedList<T>& operator=(const LinkedList<T>& other);

		size_t size() const override;
		T& operator[](const int index) override;
		const T& operator[](const int index) const override;

		void add(const T& data) override;
		void insert(const T& data, const int index) override;
		bool tryRemove(const T& data) override;
		T removeAt(const int index) override;
		int getIndexOf(const T& data) override;
		void clear() override;

		Iterator<T> begin() const override;
		Iterator<T> end() const override;
	private:
		// atributy
		size_t aSize;
		LinkedItem<T>* aFirst;
		LinkedItem<T>* aLast;

		DS::LinkedItem<T>* getLinkedItemAt(const int index) const;
	};

	template<typename T>
	LinkedList<T>::LinkedList(const EqualityFunction<T>& equalityFunction) :
		List<T>(equalityFunction),
		aSize(0),
		aFirst(nullptr),
		aLast(nullptr)
	{
	}

	template<typename T>
	LinkedList<T>::LinkedList(const LinkedList<T>& other) : LinkedList(other.equalityFunction_)
	{
		(*this) = other;
	}

	template<typename T>
	LinkedList<T>::~LinkedList()
	{
		clear();
	}

	template<typename T>
	Structure* LinkedList<T>::clone() const
	{
		return new LinkedList<T>(*this);
	}

	template<typename T>
	Structure& LinkedList<T>::operator=(const Structure& other)
	{
		return (*this) = dynamic_cast<const LinkedList<T>&>(other);
	}

	template<typename T>
	List<T>& LinkedList<T>::operator=(const List<T>& other)
	{
		return (*this) = dynamic_cast<const LinkedList<T>&>(other);
	}

	template<typename T>
	LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
	{
		List<T>::operator=(other);
		clear();
		for (T pom : other) {
			add(pom);
		}
		return *this;
	}

	template<typename T>
	size_t LinkedList<T>::size() const
	{
		return aSize;
	}

	template<typename T>
	T& LinkedList<T>::operator[](const int index)
	{
		return getLinkedItemAt(index)->getData();
	}

	template<typename T>
	const T& LinkedList<T>::operator[](const int index) const
	{
		return getLinkedItemAt(index)->getData();
	}

	template<typename T>
	void LinkedList<T>::add(const T& data)
	{
		LinkedItem<T>* pom = new LinkedItem<T>(data);
		if (aSize == 0) {
			aFirst = pom;
			aLast = pom;
		}
		else {
			aLast->setNext(pom);
			aLast = pom;
		}
		aSize++;
	}

	template<typename T>
	void LinkedList<T>::insert(const T& data, const int index)
	{
		DSRoutines::rangeCheck(index, aSize + 1, true, &std::string("Index out of range in LinkedList!"));
		if (index == aSize) {
			add(data);
		}
		else {
			LinkedItem<T>* prvok = new LinkedItem<T>(data);
			if (index == 0) {
				prvok->setNext(aFirst);
				aFirst = prvok;
			}
			else {
				LinkedItem<T>* pred = getLinkedItemAt(index - 1);
				prvok->setNext(pred->getNext());
				pred->setNext(prvok);
			}
			aSize++;
		}
	}

	template<typename T>
	bool LinkedList<T>::tryRemove(const T& data)
	{
		int index = getIndexOf(data);
		if (index == -1) {
			return false;
		}
		else {
			removeAt(index);
			return true;
		}
	}

	template<typename T>
	T LinkedList<T>::removeAt(const int index)
	{
		DSRoutines::rangeCheck(index, aSize, true, &std::string("Index out of range in LinkedList!"));

		LinkedItem<T>* mazany;
		if (index == 0) {
			mazany = aFirst;
			aFirst = aFirst->getNext();
			if (aLast == mazany) {
				aLast = nullptr;
			}
		}
		else {
			LinkedItem<T>* pred = getLinkedItemAt(index - 1);
			mazany = pred->getNext();
			pred->setNext(mazany->getNext());
			if (aLast == mazany) {
				aLast = pred;
			}
		}
		aSize--;
		T data = mazany->getData();
		//delete mazany; // na tomto to spadne 
		return data;
	}

	template<typename T>
	int LinkedList<T>::getIndexOf(const T& data)
	{
		LinkedItem<T>* pom = aFirst;
		int index = 0;

		while (pom != nullptr) {
			if (equalityFunction_(data, pom->getData())) {
				return index;
			}
			pom = pom->getNext();
			index++;
		}
		return -1;
	}

	template<typename T>
	void LinkedList<T>::clear()
	{
		LinkedItem<T>* mazany = aFirst;
		while (mazany) {
			LinkedItem<T>* dalsi = mazany->getNext();
			delete mazany;
			mazany = dalsi;
		}
		aFirst = nullptr;
		aLast = nullptr;
		aSize = 0;
	}

	template<typename T>
	Iterator<T> LinkedList<T>::begin() const
	{
		return Iterator<T>(LinkedList<T>::LinkedListIterator(aFirst));
	}

	template<typename T>
	Iterator<T> LinkedList<T>::end() const
	{
		return Iterator<T>(LinkedList<T>::LinkedListIterator(nullptr));
	}

	template<typename T>
	LinkedItem<T>* LinkedList<T>::getLinkedItemAt(const int index) const
	{
		DSRoutines::rangeCheck(index, aSize, true, &std::string("Index out of range in LinkedList!"));
		if (index != aSize - 1) {
			LinkedItem<T>* pom = aFirst;
			for (int i = 0; i < index; i++)
				pom = pom->getNext();
			return pom;
		}
		else {
			return aLast;
		}
	}

	template<typename T>
	LinkedList<T>::LinkedListIterator::LinkedListIterator(const LinkedItem<T>* item) :
		aItem(item)
	{
	}

	template<typename T>
	bool LinkedList<T>::LinkedListIterator::operator!=(const StructureIterator<T>& other) const
	{
		const LinkedListIterator& lli = dynamic_cast<const LinkedListIterator&>(other);
		return aItem != lli.aItem;
	}

	template<typename T>
	const T& LinkedList<T>::LinkedListIterator::operator*() const
	{
		return aItem->getData();
	}

	template<typename T>
	const StructureIterator<T>& LinkedList<T>::LinkedListIterator::operator++()
	{
		aItem = aItem->getNext();
		return *this;
	}

	template<typename T>
	StructureIterator<T>* LinkedList<T>::LinkedListIterator::clone() const
	{
		return new LinkedListIterator(aItem);
	}
}

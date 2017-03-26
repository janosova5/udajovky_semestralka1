#pragma once

#include "PriorityQueue.h"
#include "PriorityQueue_ArrayList.h"
#include "DSRoutines.h"
namespace DS {
	template<typename T>
	class PriorityQueue_Heap :
		public PriorityQueue_ArrayList<T>
	{
	public:
		PriorityQueue_Heap();
		PriorityQueue_Heap(const PriorityQueue_Heap<T>& other);

		Structure* clone() const override;
		PriorityQueue_Heap<T>& operator=(const PriorityQueue_Heap<T>& other);

		void push(const int priority, const T& data) override;
		T pop() override;
	protected:
		int indexOfHighestPriority() const override;
	private:
		int getParentIndex(const int index);
		int getGreaterSonIndex(const int index);
	};

	template<typename T>
	PriorityQueue_Heap<T>::PriorityQueue_Heap() : PriorityQueue_ArrayList<T>()
	{

	}

	template<typename T>
	PriorityQueue_Heap<T>::PriorityQueue_Heap(const PriorityQueue_Heap<T>& other) : PriorityQueue_ArrayList<T>(other)
	{

	}

	template<typename T>
	Structure* PriorityQueue_Heap<T>::clone() const
	{

		return new  PriorityQueue_Heap<T>(*this);
	}

	template<typename T>
	PriorityQueue_Heap<T>& PriorityQueue_Heap<T>::operator=(const PriorityQueue_Heap<T>& other)
	{
		return PriorityQueue_List<T>::operator=(other);
	}

	template<typename T>
	void PriorityQueue_Heap<T>::push(const int priority, const T& data)
	{
		PriorityItem<T>* newItem = new PriorityItem<T>(priority, data);
		list_->add(newItem);
		int curIndex = list_->size() - 1;
		int parentIndex = getParentIndex(curIndex);
		while (parentIndex >= 0 && (*list_)[parentIndex]->getPriority() > (*list_)[curIndex]->getPriority()) {
			DSRoutines::swap<PriorityItem<T>*>((*list_)[parentIndex], (*list_)[curIndex]);
			curIndex = parentIndex;
			parentIndex = getParentIndex(curIndex);
		}
	}

	template<typename T>
	T PriorityQueue_Heap<T>::pop()
	{
		T pom = (*list_)[0]->getData();
		delete (*list_)[0];
		(*list_)[0] = (*list_)[list_->size() - 1];
		list_->removeAt(list_->size() - 1);
		int curIndex = 0;
		int sonIndex = getGreaterSonIndex(curIndex);
		while (sonIndex < list_->size() && (*list_)[sonIndex]->getPriority() < (*list_)[curIndex]->getPriority()) {
			DSRoutines::swap<PriorityItem<T>*>((*list_)[sonIndex], (*list_)[curIndex]);
			curIndex = sonIndex;
			sonIndex = getGreaterSonIndex(curIndex);

		}
		return pom;
	}
	template<typename T>
	inline int PriorityQueue_Heap<T>::getParentIndex(const int index)
	{
		return (index - 1) / 2;
	}

	template<typename T>
	inline int PriorityQueue_Heap<T>::getGreaterSonIndex(const int index)
	{
		int lsonIndex = 2 * index + 1;
		int psonIndex = 2 * index + 2;
		PriorityItem<T>* lSon = lsonIndex < list_->size() ? (*list_)[lsonIndex] : nullptr;
		PriorityItem<T>* pSon = psonIndex < list_->size() ? (*list_)[psonIndex] : nullptr;
		if (lSon != nullptr && pSon != nullptr) {
			return lSon->getPriority() < pSon->getPriority() ? lsonIndex : psonIndex;

		}
		else {

			return lsonIndex;
		}
	}


	template<typename T>
	int PriorityQueue_Heap<T>::indexOfHighestPriority() const
	{
		return 0;
	}


}

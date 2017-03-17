#pragma once

#include "PriorityQueue.h"
#include "PriorityQueue_List.h"
#include "ArrayList.h"

namespace DS {

	template<typename T>
	class PriorityQueue_ArrayList :
		public PriorityQueue_List<T>
	{
	public:
		PriorityQueue_ArrayList();
		PriorityQueue_ArrayList(const PriorityQueue_ArrayList<T>& other);
	};

	template<typename T>
	PriorityQueue_ArrayList<T>::PriorityQueue_ArrayList() : PriorityQueue_List<T>(new ArrayList<PriorityItem<T>*>())
	{

	}

	template<typename T>
	PriorityQueue_ArrayList<T>::PriorityQueue_ArrayList(const PriorityQueue_ArrayList<T>& other) : PriorityQueue_List<T>(new ArrayList<PriorityItem<T>*>())
	{
		PriorityQueue_List<T>::operator=(other);
	}

}

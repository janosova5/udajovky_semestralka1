#pragma once

namespace DS
{
#pragma region DataItem
	template<typename T>
	class DataItem
	{
	public:
		DataItem(const T& data);
		DataItem(const DataItem<T>& other);
		virtual ~DataItem();
		T& getData();
		const T& getData() const;
		void setData(const T& data);
	private:
		T data_;
	};

	template<typename T>
	DataItem<T>::DataItem(const T& data) :
		data_(data)
	{
	}

	template<typename T>
	DataItem<T>::DataItem(const DataItem<T>& other) :
		DataItem(other.data_)
	{
	}

	template<typename T>
	DataItem<T>::~DataItem()
	{
	}

	template<typename T>
	T& DataItem<T>::getData()
	{
		return data_;
	}

	template<typename T>
	const T & DataItem<T>::getData() const
	{
		return data_;
	}

	template<typename T>
	void DataItem<T>::setData(const T & data)
	{
		data_ = data;
	}
#pragma endregion DataItem


#pragma region LinkedItem
	template<typename T>
	class LinkedItem :
		public DataItem<T>
	{
	public:
		LinkedItem(const T& data);
		virtual ~LinkedItem();
		LinkedItem* getNext() const;
		void setNext(LinkedItem* next);
	private:
		LinkedItem* next_;
	};

	template<typename T>
	LinkedItem<T>::LinkedItem(const T& data) :
		DataItem<T>(data),
		next_(nullptr)
	{
	}

	template<typename T>
	LinkedItem<T>::~LinkedItem()
	{
		next_ = nullptr;
	}

	template<typename T>
	typename LinkedItem<T>* LinkedItem<T>::getNext() const
	{
		return next_;
	}

	template<typename T>
	void LinkedItem<T>::setNext(LinkedItem* next)
	{
		next_ = next;
	}
#pragma endregion LinkedItem


#pragma region PriorityItem
	template<typename T>
	class PriorityItem :
		public DataItem<T>
	{
	public:
		PriorityItem(const int priority, const T& data);
		PriorityItem(const PriorityItem<T>& other);
		virtual ~PriorityItem();
		const int getPriority() const;
	private:
		int priority_;
	};

	template<typename T>
	PriorityItem<T>::PriorityItem(const int priority, const T& data) :
		DataItem<T>(data),
		priority_(priority)
	{
	}

	template<typename T>
	PriorityItem<T>::PriorityItem(const PriorityItem<T>& other) :
		DataItem<T>(other),
		priority_(other.priority_)
	{
	}

	template<typename T>
	PriorityItem<T>::~PriorityItem()
	{
	}

	template<typename T>
	const int PriorityItem<T>::getPriority() const
	{
		return priority_;
	}
#pragma endregion PriorityItem

}

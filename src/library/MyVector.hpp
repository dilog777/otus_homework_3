#pragma once


template<class T, class Allocator = std::allocator<T>>
class MyVector
{
public:
	MyVector() = default;
	~MyVector();
	
	MyVector(const MyVector &other);
	MyVector(MyVector &&other);

	MyVector &operator=(const MyVector &other);
	MyVector &operator=(MyVector &&other);

	T at(std::size_t pos) const;
	void push_back(const T& item);

	bool isEmpty() const;
	std::size_t size() const;

	void clear();

	struct iterator
	{
		iterator(const MyVector &vector, std::size_t pos);

		iterator &operator++();
		iterator &operator--();

		T operator*() const;

		bool operator==(const iterator &other) const;
		bool operator!=(const iterator &other) const;

	private:
		const MyVector &_vector;
		std::size_t _pos{ 0 };
	};

	iterator begin() const;
	iterator end() const;

private:
	std::size_t _size{ 0 };
	std::size_t _capacity{ 0 };
	T *_data{ nullptr };

	Allocator _alloc;
};



template<class T, class Allocator>
MyVector<T, Allocator>::~MyVector()
{
	_alloc.deallocate(_data, _capacity);
}



template<class T, class Allocator>
MyVector<T, Allocator>::MyVector(const MyVector &other)
{
	_size = other._size;
	_capacity = other._capacity;
	_data = _alloc.allocate(_capacity);

	T *ptr = &other._data[other._size];
	std::copy(other._data, ptr, _data);
}



template<class T, class Allocator>
MyVector<T, Allocator>::MyVector(MyVector &&other)
{
	std::swap(_size, other._size);
	std::swap(_capacity, other._capacity);
	std::swap(_data, other._data);
	std::swap(_alloc, other._alloc);
}



template<class T, class Allocator>
MyVector<T, Allocator> &MyVector<T, Allocator>::operator=(const MyVector &other)
{
	if (&other == this)
		return *this;

	_alloc.deallocate(_data, _capacity);

	_size = other.size;
	_capacity = other._capacity;
	_data = _alloc.allocate(_capacity);

	T *ptr = &other._data[other._size];
	std::copy(other._data, ptr, _data);
	return *this;
}



template<class T, class Allocator>
MyVector<T, Allocator> &MyVector<T, Allocator>::operator=(MyVector &&other)
{
	if (&other == this)
		return *this;

	_alloc.deallocate(_data, _capacity);

	std::swap(_size, other._size);
	std::swap(_capacity, other._capacity);
	std::swap(_data, other._data);
	std::swap(_alloc, other._alloc);
	return *this;
}



template<class T, class Allocator>
T MyVector<T, Allocator>::at(std::size_t pos) const
{
	if (pos <= _size)
		return _data[pos];

	return {};
}



template<class T, class Allocator>
void MyVector<T, Allocator>::push_back(const T &item)
{
	if (_size == _capacity)
	{
		std::size_t newCapacity = _capacity * 2 + 1;
		T *newData = _alloc.allocate(newCapacity);
	
		if (_capacity > 0)
		{
			T *ptr = &_data[_size];
			std::copy(_data, ptr, newData);
		}
	
		std::swap(newData, _data);
		_alloc.deallocate(newData, _capacity);
		_capacity = newCapacity;
	}
	
	T *ptr = &_data[_size];
	::new ((void *)ptr) T(item);
	++_size;
}



template<class T, class Allocator>
bool MyVector<T, Allocator>::isEmpty() const
{
	return _size == 0;
}



template<class T, class Allocator>
std::size_t MyVector<T, Allocator>::size() const
{
	return _size;
}



template<class T, class Allocator>
void MyVector<T, Allocator>::clear()
{
	_size = 0;
}



template<class T, class Allocator>
MyVector<T, Allocator>::iterator::iterator(const MyVector& vector, std::size_t pos)
	: _vector{ vector }
	, _pos{ pos }
{
}



template<class T, class Allocator>
typename MyVector<T, Allocator>::iterator &MyVector<T, Allocator>::iterator::operator++()
{
	_pos++;
	return *this;
}



template<class T, class Allocator>
typename MyVector<T, Allocator>::iterator &MyVector<T, Allocator>::iterator::operator--()
{
	_pos--;
	return *this;
}



template<class T, class Allocator>
T MyVector<T, Allocator>::iterator::operator*() const
{
	return _vector.at(_pos);
}



template<class T, class Allocator>
bool MyVector<T, Allocator>::iterator::operator==(const MyVector<T, Allocator>::iterator &other) const
{
	return _pos == other._pos;
}



template<class T, class Allocator>
bool MyVector<T, Allocator>::iterator::operator!=(const MyVector<T, Allocator>::iterator &other) const
{
	return !(*this == other);
}



template<class T, class Allocator>
typename MyVector<T, Allocator>::iterator MyVector<T, Allocator>::begin() const
{
	return iterator{*this, 0};
}



template<class T, class Allocator>
typename MyVector<T, Allocator>::iterator MyVector<T, Allocator>::end() const
{
	return iterator{*this, _size};
}

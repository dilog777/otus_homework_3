#include <memory>

#include "BlockAllocator.h"

static const std::size_t DEFAULT_ALLOCATED_BLOCK_SIZE = 10;


template<class T>
struct MyAllocator 
{
	using value_type = T;

	MyAllocator() noexcept;

	template<class U> 
	MyAllocator(const MyAllocator<U> &other) noexcept;

	T *allocate(std::size_t n);
	void deallocate(T *ptr, std::size_t n);

	std::size_t blockSize() const;
	void setBlockSize(std::size_t blockSize);

	template<class U>
	struct rebind
	{
		typedef MyAllocator<U> other;
	};

	std::shared_ptr<BlockAllocator> _blockAllocator;
};



template<class T>
MyAllocator<T>::MyAllocator() noexcept
	: _blockAllocator{ new BlockAllocator(DEFAULT_ALLOCATED_BLOCK_SIZE * sizeof(T))}
{
}



template<class T> template<class U>
MyAllocator<T>::MyAllocator(const MyAllocator<U> &other) noexcept
{
	_blockAllocator = other._blockAllocator;
}



template<class T>
T *MyAllocator<T>::allocate(std::size_t n)
{
	return static_cast<T *>(_blockAllocator->allocate(n * sizeof(T)));
}



template<class T>
void MyAllocator<T>::deallocate(T *ptr, std::size_t /*n*/)
{
	_blockAllocator->deallocate(ptr);
}



template<class T>
std::size_t MyAllocator<T>::blockSize() const
{
	return _blockAllocator->blockSize();
}



template<class T>
void MyAllocator<T>::setBlockSize(std::size_t blockSize)
{
	_blockAllocator->setBlockSize(blockSize);
}



template<class T, class U>
constexpr bool operator==(const MyAllocator<T> &a1, const MyAllocator<U> &a2) noexcept
{
	return a1._blockAllocator == a2._blockAllocator;
}



template<class T, class U>
constexpr bool operator!=(const MyAllocator<T> &a1, const MyAllocator<U> &a2) noexcept
{
	return !(a1 == a2);
}

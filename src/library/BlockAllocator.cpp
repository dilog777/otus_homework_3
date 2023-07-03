#include <algorithm>

#include "BlockAllocator.h"



BlockAllocator::BlockAllocator(std::size_t blockSize)
	: _blockSize{ blockSize }
{
}



BlockAllocator::~BlockAllocator()
{
	for (const auto &bi : _globalBlocks)
		::operator delete(bi.ptr);
}



void *BlockAllocator::allocate(std::size_t size)
{
	auto compareFunc = [size](const BlockInfo &bi) { return (!bi.busy && bi.size >= size); };
	auto it = std::find_if(_allocatedBlocks.begin(), _allocatedBlocks.end(), compareFunc);
	if (it == _allocatedBlocks.end())
	{
		auto blockSize = std::max(_blockSize, size);
		
		auto memoryPtr = ::operator new(blockSize);
		if (!memoryPtr)
			throw std::bad_alloc();

		_globalBlocks.push_back(BlockInfo{ memoryPtr, blockSize });
		_allocatedBlocks.push_back(BlockInfo{ memoryPtr, blockSize });
		it = std::prev(_allocatedBlocks.end());
	}

	occupyBlock(it, size);
	return it->ptr;
}



void BlockAllocator::deallocate(void *ptr)
{
	auto compareFunc = [ptr](const BlockInfo &bi) { return (bi.ptr == ptr); };
	auto it = std::find_if(_allocatedBlocks.begin(), _allocatedBlocks.end(), compareFunc);
	if (it != _allocatedBlocks.end())
		releaseBlock(it);
}



std::size_t BlockAllocator::blockSize() const
{
	return _blockSize;
}



void BlockAllocator::setBlockSize(std::size_t blockSize)
{
	_blockSize = blockSize;
}



void BlockAllocator::occupyBlock(const BlockInfoIt &it, std::size_t size)
{
	if (it->size > size)
	{
		BlockInfo freeBlock;
		freeBlock.ptr = static_cast<char *>(it->ptr) + size;
		freeBlock.size = it->size - size;
		_allocatedBlocks.insert(std::next(it), freeBlock);

		it->size = size;
	}

	it->busy = true;
}



void BlockAllocator::releaseBlock(const BlockInfoIt &it)
{
	it->busy = false;
	
	auto nextIt = std::next(it);
	if (nextIt != _allocatedBlocks.end())
	{
		bool neighborsPtr = (static_cast<char *>(it->ptr) + it->size == nextIt->ptr);
		if (!nextIt->busy && neighborsPtr)
		{
			it->size += nextIt->size;
			_allocatedBlocks.erase(nextIt);
		}
	}

	if (it != _allocatedBlocks.begin())
	{
		auto prevIt = std::prev(it);
		bool neighborsPtr = (static_cast<char *>(prevIt->ptr) + prevIt->size == it->ptr);
		if (!prevIt->busy && neighborsPtr)
		{
			prevIt->size += it->size;
			_allocatedBlocks.erase(it);
		}
	}
}

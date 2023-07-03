#include <iostream>
#include <map>
#include <vector>

#include "MyAllocator.hpp"
#include "MyVector.hpp"


template<typename M>
void fillMapByFactorial(M &map, std::size_t size)
{
	if (!size)
		return;
	
	map[0] = 1;
	for (std::size_t i = 1; i < size; ++i)
		map[i] = map[i - 1] * i;
}



template<typename M>
void printMap(const M &map)
{
	for (const auto &pair : map)
		std::cout << pair.first << " " << pair.second << std::endl;
}



template<typename V>
void fillVectorByRange(V &vector, std::size_t size)
{
	for (std::size_t i = 0; i < size; ++i)
		vector.push_back(i);
}



template<typename V>
void printVector(const V &vector)
{
	for (const auto &value : vector)
		std::cout << value << std::endl;
}



int main()
{
	const std::size_t size = 10;
	
	std::map<int, int> map1;
	fillMapByFactorial(map1, size);
	//printMap(map1);

	std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>>> map2;
	fillMapByFactorial(map2, size);
	printMap(map2);

	MyVector<int> vector1;
	fillVectorByRange(vector1, size);
	//printVector(vector1);

	MyVector<int, MyAllocator<int>> vector2;
	fillVectorByRange(vector2, size);
	printVector(vector2);

	return 0;
}

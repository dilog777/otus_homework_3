#include <gtest/gtest.h>

#include "MyAllocator.hpp"
#include "MyVector.hpp"



TEST(test_google_version, test_my_allocator)
{
	std::map<int, int> map1;
	std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>>> map2;
	
	const int size = 100;
	for (int i = 0; i < size; ++i)
	{
		int key = rand();
		int value = rand();
		map1[key] = value;
		map2[key] = value;
	}

	EXPECT_TRUE(map1.size() == map2.size());

	for (const auto &pair : map1)
		EXPECT_TRUE(map2[pair.first] == pair.second);
}



TEST(test_google_version, test_my_vector)
{
	std::vector<int> vector1;
	MyVector<int> vector2;

	const int size = 100;
	for (int i = 0; i < size; ++i)
	{
		int value = rand();
		vector1.push_back(value);
		vector2.push_back(value);
	}

	EXPECT_TRUE(vector1.size() == vector1.size());

	for (std::size_t i = 0; i < vector1.size(); ++i)
		EXPECT_TRUE(vector1.at(i) == vector2.at(i));
}



TEST(test_google_version, test_my_vector_with_my_allocator)
{
	MyVector<int> vector1;
	MyVector<int, MyAllocator<int>> vector2;

	const int size = 100;
	for (int i = 0; i < size; ++i)
	{
		int value = rand();
		vector1.push_back(value);
		vector2.push_back(value);
	}

	EXPECT_TRUE(vector1.size() == vector1.size());

	for (std::size_t i = 0; i < vector1.size(); ++i)
		EXPECT_TRUE(vector1.at(i) == vector2.at(i));
}




int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

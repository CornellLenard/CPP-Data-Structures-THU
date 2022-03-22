#include <iostream>
#include "skiplist_dictionary.h"


int main()
{
	SkipListDictionary<int, int> dict;

	std::cout << dict.Put(1, 11) << '\n';
	std::cout << dict.Put(2, 11) << '\n';
	std::cout << dict.Put(2, 11) << '\n';
	std::cout << dict.GetSize() << '\n';
	std::cout << *(dict.Get(1)) << '\n';
	std::cout << dict.Remove(4) << '\n';
	std::cout << dict.GetSize() << '\n';
	std::cout << dict.Remove(3) << '\n';
	std::cout << dict.GetSize() << '\n';

	for (int i = 3; i <= 11; i++)
		dict.Put(i, 11);
	std::cout << dict.GetSize() << '\n';

	return 0;
}



#include <iostream>
#include "bst_map.h"


template<typename T> class Visit
{
public:
	void operator()(const T& e)
	{
		std::cout << e << "  ";
	}
};


int main()
{
	BinarySearchTreeMap<int, int> bm;
	Visit<int> visit;

	bm.Insert(1, 1);
	bm.Insert(2, 2);
	bm.Insert(3, 3);
	std::cout << bm.GetSize() << "   " << bm.IsEmpty() << '\n';

	bm.TraverseIn(visit);
	std::cout << '\n';

	bm.Remove(3);
	std::cout << bm.GetSize() << '\n';

	bm.TraverseIn(visit);
	std::cout << '\n';

	bm.Remove(1);
	bm.Remove(2);
	std::cout << bm.GetSize();

	return 0;
}



#include <iostream>
#include "splay_tree_map.h"


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
	SplayTreeMap<int, int> stm;
	Visit<int> visit;

	stm.Insert(1, 1);
	stm.Insert(2, 2);
	stm.Insert(3, 3);
	std::cout << stm.GetSize() << "   " << stm.IsEmpty() << '\n';

	stm.TraverseIn(visit);
	std::cout << '\n';

	stm.Remove(3);
	std::cout << stm.GetSize() << '\n';

	stm.TraverseIn(visit);
	std::cout << '\n';

	stm.Remove(1);
	stm.Remove(2);
	std::cout << stm.GetSize();

	return 0;
}



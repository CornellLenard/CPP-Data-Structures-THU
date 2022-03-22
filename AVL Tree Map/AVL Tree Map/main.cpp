#include <iostream>
#include "avl_tree_map.h"


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
	AVLTreeMap<int, int> am;
	Visit<int> visit;

	am.Insert(1, 1);
	am.Insert(2, 2);
	am.Insert(3, 3);
	std::cout << am.GetSize() << "   " << am.IsEmpty() << '\n';

	am.TraverseIn(visit);
	std::cout << '\n';

	am.Remove(3);
	std::cout << am.GetSize() << '\n';

	am.TraverseIn(visit);
	std::cout << '\n';

	am.Remove(1);
	am.Remove(2);
	std::cout << am.GetSize();

	return 0;
}



#include <iostream>
#include "binary_tree.h"


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
	BinaryTree<int> bt;
	Visit<int> visit;

	bt.InsertAsRoot(2);
	bt.InsertAsLC(bt.GetRoot(), 1);
	bt.InsertAsRC(bt.GetRoot(), 3);
	std::cout << bt.GetSize() << "  " << bt.IsEmpty() << '\n';

	bt.TraverseIn(visit);
	std::cout << '\n';

	bt.Remove(bt.GetRoot()->lc_);
	bt.Remove(bt.GetRoot()->rc_);
	std::cout << bt.GetSize() << '\n';

	bt.TraverseIn(visit);
	std::cout << '\n';

	bt.Remove(bt.GetRoot());
	std::cout << bt.IsEmpty();

	return 0;
}



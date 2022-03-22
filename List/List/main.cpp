#include <iostream>
#include "list.h"


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
	List<int> lst;
	Visit<int> visit;

	for (int i = 1; i <= 6; i++)
		lst.InsertAsFirst(i);

	for (int i = 0; i < 7; i++)
		lst.InsertAsLast(7);

	for (int i = 11; i >= 8; i--)
		lst.InsertAsLast(i);

	lst.Traverse(visit);
	std::cout << '\n';

	lst.Deduplicate();
	lst.Traverse(visit);
	std::cout << '\n';

	std::cout << lst.GetSize() << "  " << lst.IsEmpty() << '\n';
	std::cout << (lst.Find(7))->data_ << '\n';

	lst.Sort();
	lst.Traverse(visit);
	std::cout << '\n';

	lst.Reverse();
	lst.Traverse(visit);

	return 0;
}



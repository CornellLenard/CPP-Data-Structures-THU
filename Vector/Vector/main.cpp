#include <iostream>
#include "vector.h"


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
	Vector<int> vec;
	Visit<int> visit;

	for (int i = 1; i <= 6; i++)
		vec.Insert(i);

	for (int i = 0; i < 6; i++)
		vec.Insert(7);

	for (int i = 11; i > 7; i--)
		vec.Insert(i);

	std::cout << vec.GetSize() << "  " << vec.IsEmpty() << "  " << vec.Disordered() << '\n';

	vec.Traverse(visit);
	std::cout << '\n';

	vec.Uniquify();
	vec.Traverse(visit);
	std::cout << '\n';

	vec.Insert(12);
	vec.Remove(vec.GetSize() - 1);
	vec.Traverse(visit);
	std::cout << '\n';

	vec.Sort();
	vec.Traverse(visit);

	return 0;
}



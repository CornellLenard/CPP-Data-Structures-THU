#include <iostream>
#include "stack.h"


int main()
{
	Stack<int> st;

	for (int i = 1; i <= 11; i++)
		st.Push(i);

	std::cout << st.GetSize() << "  " << st.IsEmpty() << '\n';

	for (int i = 0; i < 11; i++)
		std::cout << st.Pop() << "  ";

	return 0;
}



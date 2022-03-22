#include <iostream>
#include "queue.h"


int main()
{
	Queue<int> q;

	for (int i = 1; i <= 11; i++)
		q.Enqueue(i);

	std::cout << q.GetSize() << "  " << q.IsEmpty() << '\n';

	for (int i = 0; i < 11; i++)
		std::cout << q.Dequeue() << " ";

	return 0;
}



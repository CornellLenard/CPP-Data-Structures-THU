#include <iostream>
#include "priority_queue_array_heap.h"


int main()
{
	PriorityQueueArrayHeap<int> pq;

	pq.Insert(1);
	pq.Insert(2);
	pq.Insert(3);
	std::cout << pq.GetSize() << "   " << pq.IsEmpty() << '\n';

	for (int i = 0; i < 3; i++)
		std::cout << pq.DeleteMax() << "  ";

	return 0;
}



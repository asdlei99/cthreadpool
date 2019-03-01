#include "ctask_operation.h"
#include "cthreadpool.h"
#include <iostream>

cthread_pool<ctask_operation> * pool = NULL;

void _create()
{
	for (int i = 0; i < 30000; ++i)
	{
		ctask_operation *task = new ctask_operation;
		if (task)
		{
			task->init(i);
			while (!pool->append(task)) {}
		}
	}
}

int main(int argc, char *argv[])
{
	////////////////////////////////////////////
	// init thread_pool 
	
	pool = new cthread_pool<ctask_operation>;
	if (!pool)
	{
		std::cout << "alloc error" << std::endl;
		return -1;
	}
	pool->init(5, 500);
	pool->start();
	std::vector<std::thread> procuse;
	for (int i = 0; i < 9; ++i)
	{
		 
		procuse.emplace_back(std::thread(_create));
	}
	for (std::thread &thread : procuse)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
	procuse.clear();
	
	pool->Destroy();
	if (pool)
	{
		delete pool;
		pool = NULL;
	}

	return EXIT_SUCCESS;
}
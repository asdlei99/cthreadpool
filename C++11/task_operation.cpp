#include "task_operation.h"
#include <iostream>
//#include <windows.h>


bool task_operation::init(int sum)
{
	m_task = sum;
	return true;
}

void task_operation::Destroy()
{
}

void task_operation::process()
{
	//Sleep(20);
	printf("[%s][%d] sum = %d", __FUNCTION__, __LINE__, m_task);
	delete this;
}

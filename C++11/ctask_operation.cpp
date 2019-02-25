#include "ctask_operation.h"
#include <iostream>
//#include <windows.h>


bool ctask_operation::init(int sum)
{
	m_task = sum;
	return true;
}

void ctask_operation::Destroy()
{
}

void ctask_operation::process()
{
	//Sleep(20);
	printf("[%s][%d] sum = %d", __FUNCTION__, __LINE__, m_task);
	delete this;
}

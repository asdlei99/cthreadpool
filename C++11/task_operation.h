#pragma once
#include "cnoncopyable.h"
class task_operation :public cnoncopyable
{
public:
	explicit task_operation(){}
	
	virtual ~task_operation(){}
public:
	bool init(int sum);
	void Destroy();
	void process();
private:
	int		m_task;
};


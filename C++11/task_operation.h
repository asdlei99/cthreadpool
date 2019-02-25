#pragma once
class task_operation
{
public:
	task_operation();
	
	~task_operation();
public:
	bool init(int sum);
	void Destroy();
	void process();
private:
	int		m_task;
};


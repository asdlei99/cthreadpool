#ifndef _C_TASK_OPERATION_H_
#define _C_TASK_OPERATION_H_
#include "cnoncopyable.h"
class ctask_operation :public cnoncopyable
{
public:
	explicit ctask_operation(){}
	
	virtual ~ctask_operation(){}
public:
	bool init(int sum);
	void Destroy();
	void process();
private:
	int		m_task;
};
#endif  //_C_THREADPOOL_H_

#ifndef _C_NONCOPYABLE_H_
#define _C_NONCOPYABLE_H_

class cnoncopyable
{
public:
	explicit cnoncopyable() {}
	virtual ~cnoncopyable() {}
private:
	cnoncopyable(const cnoncopyable&);
	cnoncopyable& operator=(const cnoncopyable&);
};
#endif // _C_NONCOPYABLE_H_


// Chris Vasquez

using namespace std;

#include <unistd.h>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <sstream>

class SimpleReadWriteLock{
   private:
	int readers;
	bool writer;
	std::thread::id wOwner;
	std::thread::id nullId;
	int waitWriters;
        recursive_mutex mtx;
	condition_variable_any condition;

   public:

	SimpleReadWriteLock();

	~SimpleReadWriteLock();

	void rLock(int num);

	void rUnlock(int num);

	void wLock(int num);

	void wUnlock(int num);
};

/*
	Read Write Lock class
*/


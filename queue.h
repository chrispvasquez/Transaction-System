using namespace std;

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <sstream>
#include <atomic>
#include <queue>

// Standard queue made thread safe with use of locks

template<class T>
class threadSafeQueue{
     private:
        queue<T> myQueue;
	mutex mtx;

	bool empty() const{
	   return myQueue.empty();
	}

     public:

	threadSafeQueue(){};
	~threadSafeQueue(){};

	void push(T x){
	   lock_guard<mutex> lock(mtx);
	   myQueue.push(x);
	}

	T pop(){
	   lock_guard<mutex> lock(mtx);
	   if(myQueue.empty()){
	      cout << "ERROR: QUEUE EMPTY\n";
	      exit(1);
	   }
	   T temp = myQueue.front();
	   myQueue.pop();
	   return temp;
	}

	int size(){
	   lock_guard<mutex> lock(mtx);
	   return myQueue.size();
	}
};

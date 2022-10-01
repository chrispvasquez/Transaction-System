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
#include "ReadWriteLock.h"


SimpleReadWriteLock::SimpleReadWriteLock(){
	   writer = false;
	   readers = 0;
	   waitWriters = 0;
	}

SimpleReadWriteLock::~SimpleReadWriteLock(){};


void SimpleReadWriteLock::rLock(int num){

	   unique_lock<recursive_mutex> lock(mtx);

	   while (writer){
	    condition.wait(lock);
	   }
	   readers++;
}


void SimpleReadWriteLock::rUnlock(int num){
	   unique_lock<recursive_mutex> lock(mtx);
	   readers--;

	   if(readers == 0) condition.notify_all();
}


void SimpleReadWriteLock::wLock(int num){

	   auto me = this_thread::get_id();
	   unique_lock<recursive_mutex> lock(mtx);

	   if(wOwner == me){
	     waitWriters++;
	     return;
	   }

	   while ((readers > 0 || writer) && waitWriters != 0) {
	      condition.wait(lock);
	   }

	   writer = true;
	   wOwner = me;
	   waitWriters = 1;
}


void SimpleReadWriteLock::wUnlock(int num){

	   unique_lock<recursive_mutex> lock(mtx);

	   auto me = this_thread::get_id();

	   if(waitWriters == 0 || wOwner != me)	cout << "ILLEGAL MONITOR STATE EXCEPTION\n";

	   waitWriters--;

	   if(waitWriters == 0){
	     wOwner = nullId;
	     writer = false;
	     condition.notify_all();
	  }
}


//Chris Vasquez

using namespace std;
// Namespace

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <sstream>
#include "ReadWriteLock.h"
#include "database.h"
#include "queue.h"
// Libraries

int main(){

	int n = 10; 				// Configurabe # of threads
	string inputFile = "input.txt";		// Input Text File
	string commandFile = "command.txt";	// Command text File


	vector<thread> threads;					// Vector for threads
	SimpleReadWriteLock *L = new SimpleReadWriteLock();	// ReadWrite lock
	myDatabase data(inputFile); 				// Insert database entries
	threadSafeQueue<vector<string>> commands;


	// Open file and extract command data into a thread safe queue
	// where: command[i][j], where i = line number of text file & j = command(0), key(1), value(2)

	fstream myFile;
	string command, first, last, value;
	myFile.open(commandFile.c_str());

	while(myFile >> command){
	  myFile >> first;
	  myFile >> last;
	  string key = first + " " + last;
	  vector<string> tempVect;
	  tempVect.push_back(command);
	  tempVect.push_back(key);
	  if(command == "insert" || command == "update"){
	   myFile >> value;
	   tempVect.push_back(value);
	  }
	   commands.push(tempVect);
	}

	myFile.close();


	// Use assembled queue distribute work to threads based on the command work

	for(int i = 0; i < n; i++){

	   threads.push_back(thread([&L, i, &commands, &data]() mutable {
	   while(commands.size() != 0){

	     vector<string> c = commands.pop();

	     if(c[0] == "insert"){
	         L->wLock(i);
	         if(!data.checkKey(c[1]))
	           data.insert(c[1], stod(c[2]));
	         else {
	           stringstream s;
	           s << "Error: User \"" << c[1] <<  "\" already exists!\n";
		   cout << s.str();
	         }
	         L->wUnlock(i);
	     }

	     else if(c[0] == "update"){
	         L->wLock(i);
	         if(data.checkKey(c[1])){
	            if((data.get(c[1], false) + stod(c[2])) >= 0.0)
	              data.update(c[1], stod(c[2]));
	            else{
	              stringstream s;
	              s << "Error: User \"" << c[1] << "'s\" withdrawl is too large for current balance!\n";
		      cout << s.str();
	            }
	         }

	         else{
	           stringstream s;
	           s << "Error: User \"" << c[1] <<  "\" was not found!\n";
		   cout << s.str();
	         }
	         L->wUnlock(i);
	     }

	     else if(c[0] == "remove"){
	         L->wLock(i);
	         if(data.checkKey(c[1]))
	           data.remove(c[1]);
	         else {
		   stringstream s;
	           s << "Error: User \"" << c[1] <<  "\" was not found!\n";
		   cout << s.str();
	         }
	         L->wUnlock(i);
	     }

	     else if(c[0] == "get"){
	         L->rLock(i);
	         if(data.checkKey(c[1]))
	           double temp = data.get(c[1], true);
	         else {
		   stringstream s;
	           s << "Error: User \"" << c[1] <<  "\" was not found!\n";
		   cout << s.str();
	         }
	         L->rUnlock(i);
	     }

	     else {
	       stringstream s;
	       s << "Error Invalid Command: \"" << c[0] << "\"";
	       cout << s.str();
	       exit(1);
	     }
	  }

	  }));

	}

	for(auto j = threads.begin(); j != threads.end(); ++j)
	   j->join();

	data.outputData(); // Place edited database into a text file in alphabetical order

	return 0;
}

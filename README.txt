Chris Vasquez
11/26/2020
---------------------------------------------

Program:

This program uses a NO-SQL database and mimicks a bank with the standard transactions of
inserting, remvoing, updating, and getting. An input text file may be provided if one would like to use 
their own perviously compiled data. A command text file should be provided if one would like to perform any type
of transactions on their provided data. An output text file will be generated to show all changes made to the
database and any provided data.


To Run Program:
-----------------
./a.out

To Compile:
----------------
make

Files:
----------------
1) "main.cpp"
2) "queue.h"
3) "database.h"
4) "ReadWriteLock.h"
5) "ReadWriteLock.cpp"


Descriptions:
----------------
1) Contains code for a database program base around standard bank transactions.

2) Contains the code for a thread safe queue

3) Contains the code for a NO-SQL database implementation using an unordered_map;
   Database operations include:
	insert: Adding a new item to the database
	remove: Remove item from database
	update: Add to / subtract from the current value within the database
	get: get the current value stored at a given key

4) & 5) Contains code for a Read Write Lock


Notes:
-----------------
	*Updating the current value in the database does not replace the value, but rather increments/decrements it.

	*Error messages will be shown if an invalid command is entered (or improper input/command file formatting), 
	 withdrawls bigger than the current allowed balance, inserting a user who is already in the data base, and
	 attempting to remove someone not in the database.

	*Commands that lead to errors will be skipped and will not affect the database


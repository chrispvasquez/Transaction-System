using namespace std;

#include <fstream>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

class myDatabase{

	private:
	   unordered_map<string, double> database;

	public:

	   // If input file prsent, insert data into database
	   myDatabase(string filename){
		fstream myFile;
		string first, last, value;
		myFile.open(filename.c_str());

		while(myFile >> first){
	  	  myFile >> last;
	  	  string key = first + " " + last;
	  	  myFile >> value;
		  double v = stod(value);
	  	  database.insert({key, v});
		}

		myFile.close();
	   }

	   myDatabase(){};
	   ~myDatabase(){};
	   void insert(string, double);	// Insert item
	   void remove(string);		// Remove item
	   double get(string, bool);	// Get item
	   void update(string, double);	// Add to/ subtract from item
	   bool checkKey(string);	// check if key exists
	   void outputData();		// Output data into text file named "output.txt"
};


void myDatabase::insert(string k, double v){
	stringstream s;
	database.insert({k, v});
	s << k << " was inserted into the database with a balance of $";
	s << setprecision(2) << fixed << v << "\n";
	cout << s.str();
}

void myDatabase::remove(string k){
	stringstream s;
	database.erase(k);
	s << k << " was removed from the database.\n";
	cout << s.str();
}

double myDatabase::get(string k, bool b){
	auto it = database.find(k);

	if(b){
	  stringstream s;
	  s << k << "'s current blance is $";
	  s << setprecision(2) << fixed << it->second << "\n";
	  cout << s.str();
	}

	return it->second;
}

void myDatabase::update(string k, double v){
	stringstream s;
	auto it = database.find(k);
	it->second = it->second + v;

	if(v >=0){
	  s << k << " has deposited $";
	  s << setprecision(2) << fixed << v << ", New Balance: $";
	  s << setprecision(2) << fixed << it->second << "\n";
	}
	else{
	  s << k << " has withdrawn $";
	  s << setprecision(2) << fixed << -v << ", Remaining Balance: $";
	  s << setprecision(2) << fixed << it->second << "\n";
	}

	cout << s.str();
}

bool myDatabase::checkKey(string k){
	if(database.find(k) == database.end())
	   return false;
	return true;
}

void myDatabase::outputData(){
	ofstream myfile;
	myfile.open("output.txt");
	map<string, double> order(database.begin(), database.end());
	for(auto it = order.begin(); it != order.end(); ++it){
	   myfile << it->first;
	   myfile << " ";
	   myfile << setprecision(2) << fixed << it->second << '\n';
	}

	myfile.close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/*
Project 1- DNA Analysis
main.cpp
Caleb Satvedi
CS 251 Sp 2022
Description: This is the full implementation for the DNA analysis project. Because
our containers are limited to the ourvector, I had to be creative in how I stored the 
different files of data. The below code includes parsing through text files, analyzing
ourvector data in order to see similarities in DNA, and filling different databases.
*/


#include "ourvector.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;
/* Over here, I have made the DNA a struct so it can be easily accessed.
The model 2d ourvector (first one) is a ourvector<ourvector<char>> which contains the names of the STR's that are in the database.
The database 2d vector (2nd one) contains the names of the people and the number of differnt consecutive STRs. 
The thrid one is a 1d ourvector containing the letters in the DNA sequecne. 
The fourth one is how many of each consecutive STR in the DNA strand. Note this fourth ourvector and 1st one are going to have the same size.
*/
struct DNA{
	ourvector<ourvector<char>> model;
	ourvector<ourvector<char>> database;
	ourvector <char> dna;
	ourvector<int> strCount;
};
/*This function here is called from the load_db function, and takes in the DNA user struct as a reference parameter and the modeler string, which is the first line of the small or large.txt. 
It then formats the first line into the model ourvector, which is part of the user struct. 
*/
void readInModel( DNA & user, string modeler){
	//we will use this ourvector mod to push back in the 2d ourvector model
	ourvector <char> mod;
	//use a stringstream operation
	stringstream s(modeler);
	//dummy string str will hold values of the STR's
	string str;
	//i will be the counter variable as we go through the modeler string
	int i = 0;
	while(i <= modeler.size()) {
		//use getline from stringstream to get the values of each str 
		// uses comma as a delimiter, puts the value in str variable
		getline(s, str, ',');
		//the for loop below puts each character of str into the mod ourvector
		for(int j = 0; j < str.size(); j++) {
			//we use push_back here as a function of the overvector class
			mod.push_back(str[j]);
		}
	//we use push_back(auto) here as a function of the ourvector class
		user.model.push_back(mod);
	//we use clear to clear the mod vector so it is ready for the next str
	//clear() is used as a fucntion form the ourvector class
		mod.clear();
		i = str.size() + i + 1;
	}
}

/* Similar to the one above it, the readInPPLData fucntion is called from the load_db function. 
It takes in the DNA user struct as a reference parameter and the udata string, which is a line from small.txt or large.txt. 
It then formats the that into the database ourvector, which is part of the user struct. 
*/
void readInPPLData(DNA & user, string udata){
	//we will use this ourvector mod to push back in the 2d ourvector database
		ourvector <char> uvec;
		//l will be the counter for the string we send in
		int l = 0;
		while(l < udata.size()) {
			//here, we push each character of the string into the ourvector
			//if the character is a comma, we replace it with a space
			if(udata[l] == ',') {
				uvec.push_back(' ');
			} else {
			uvec.push_back(udata[l]);}
			l++;
		}
		//we push back the uvec ourvector into the 2D ourvector database
		//we clear the uvec ourvector for the next string to come
		//push_back() and clear() are all part of the ourvector class
		user.database.push_back(uvec);
		uvec.clear();
}

/* This load_db function takes in the string textfile(either small.txt or large.txt) and DNA user struct and loads the database ourvector and the model ourvector.
First, it reads in the file, and takes the first line of the file and formats that into the model ourvector. This is done in the readInModel function above.
Next, it reads in the rest of the file and formats that into the database ourvector. This is done in the readInPPLData function above.
*/
void load_db(string textFile, DNA& user) {
	//we open the file, and if we can't open it, we display that fact
	cout << "Loading database..."<<endl;
     ifstream newFile;
     newFile.open(textFile);
     if (!newFile.is_open()) {
    	 cout << "Error: unable to open \'" << textFile << "\'" << endl;
     return;
   }//we use the modeler string and getline() to get the first line of the file
    string modeler;
    getline(newFile, modeler);
    //we then call in readInModel to format the modeler ourvector
    readInModel(user, modeler);
 	string udata;
	while( ! newFile.eof()) {
		//we use string udata here to read in each line of the file
		//we then call up readInPPLData to format that string into the 
		//2d ourvector database. 
		//readInPPLData is consistently called 
		getline(newFile, udata);
		readInPPLData(user, udata);
	}}
/*Below function is called to format the #.txt for the DNA strand. 
This function takes in the name of the text file and the user DNA struct
as a reference variable.
*/
void load_dna(string textFile, DNA& user) {
	//we load the text file, adn if we can't find the file, we let user know
	cout << "Loading DNA..." << endl;
     ifstream newFile;
     newFile.open(textFile);
     if (!newFile.is_open()) {
     cout << "Error: unable to open \'" << textFile << "\'" << endl;
     return;
   }
   //strand is used to get each line of dna
	string strand;
   while( !newFile.eof()) {
   	//getline is used to get eachline of the text file,
   	//we put that line into the strand variable
		getline(newFile, strand);
		//i is the counter for strand
		//we put each character of strand into the dna ourvector from DNA user struct
		for(int i = 0; i < strand.size();i++) {
			user.dna.push_back(strand[i]);
		}
   }
}

//below function is used to display the facts of the DNA
//It takes in the user DNA struct
void display(DNA user) {
	//we check if database ourvector is loaded
	//If so, we display 
	//If not we let the user know
	if(user.database.size() == 0) {
		cout << "No database loaded." << endl;
		} else {
	cout << "Database loaded:" << endl;
	for(int i = 0; i < user.database.size(); i++) {
		for(int j = 0; j < user.database[i].size(); j++) {
			cout << user.database[i][j];}
		cout << endl; }}
	//we check if DNA ourvector is loaded
	//If so, we display 
	//If not we let the user know
	if(user.dna.size() == 0){
		cout << "No DNA loaded." << endl << endl;
	}else{
		cout<<"DNA loaded:"<<endl;
		for(int j = 0; j< user.dna.size(); j++){
			cout<<user.dna[j];}
		cout<<endl<<endl;}
	//we check if strCount ourvector is loaded
	//If so, we display 
	//If not we let the user know
	if(user.strCount.size()==0){
		cout<<"No DNA has been processed."<<endl;
	} else {
		cout<<"DNA processed, STR counts: "<<endl;
		for(int i = 1; i < user.strCount.size(); i++){
			for(int j = 0; j < user. model[i].size(); j++){
				cout<<user.model[i][j]; }
			cout<<": "<<user.strCount[i]<<endl; }
		cout<<endl; }
	}
/* This countSTR function below is called by the process function underneath
This function takes in the user DNA struct as a refernce parameter
It will count how many of each str is present in the DNA strand
*/
void countStr(DNA& user){
	//Remember, the strCount and the model ourvectors in the user struct
	//must have the same size, 
	//Because the model ourvector begins with name, we must push_back
	//0 in the strCount ourvector
	user.strCount.push_back(0);
	//We use o as the counter for the model ourvector
	int o = 1; 
	while(o < user.model.size()){
		/*We are going to format this in 2 noticeable manners
		The first is finding where the str is present in dna
		We will look for where the first letter of the str is present
		in the DNA. We will use i as a counter to go through the entire dna 
		ourvector. 
		*/
		//Max is the max amount of times the str is repeated consecutively
		// curr is the current amount of times the str is repated consecutively
		int max=0;
		int curr= 0;
		int i = 0;
		while(i < user.dna.size() - user.model[o].size()){
			//Deviate will check if the full str is present consectuively
			bool deviate = false;
			//if the current character is equal to the first character
			//of the str, we can then start this process
			if(user.dna[i] == user.model[o][0]){
				//J will be the counter to go through the model[o] ourvector
				for(int j = 1; j< user.model[o].size(); j++){
					//below checks to see if the following values
					//of the dna and str match up
					if(user.dna[i+j] != user.model[o][j]){
						//if they dont, we set curr to 0 and deviate to true
					curr = 0;
					deviate = true;
			 		}}
			 		//if it deviated, we only increment i by 1
				if(deviate){
					i++;
				} else{
					//if it didn't deviate, we can then increment i by the
					// str size, as well as the curr by 1
				i+= user.model[o].size();
				curr++;	
				}} else{
					//this else is for if the current dna didn't equal
					//the first letter of the str
			i++;}
			/*The next is to see what is the max consecutive presence 
		of the repeated str. Think of finding the max value in a 
		container. We check if the current value is larger that the 
		current max, and if so, we switch it out.*/
			if(curr > max){
				max = curr;	}}
		//we increment o here to check for the next str
		o++;
		//we push back bax into the strCount struct
		user.strCount.push_back(max);}
	return;}	
/* This function proccesses the DNA. It takes in the user DNA struct as 
a reference parameter.
*/
void process(DNA& user){
	//We first ensure the database and dna is loaded
	if(user.database.size()==0){
		cout<<"No database loaded."<<endl;
		return;
	}
	if(user.dna.size()==0){
		cout<<"No DNA loaded."<<endl;
		return;
	}
	cout<<"Processing DNA..."<<endl;
	//The countSTR function called below will count the # of each str
	//in the dna strand
	countStr( user);
	return;
}

/* This is the helper function for findAllSTR.
It takes in a user DNA struct.
It is similar to countStr function above,
Instead, this will count all the strs, no matter 
the consecutiveness. The only difference in the 
code is that this function does not use a max vs curr
statment. 
*/
void countAllSTR(DNA user){
	int o = 1; 
	while(o < user.model.size()){
		int curr= 0;
		int i = 0;
		while(i < user.dna.size() - user.model[o].size()){
			bool deviate = false;
			if(user.dna[i] == user.model[o][0]){
				for(int j = 1; j< user.model[o].size(); j++){
					if(user.dna[i+j] != user.model[o][j]){
					deviate = true;
			 		}}
				if(deviate){
					i++;
				}else{
				i+= user.model[o].size();
				curr++;	
				}
			}else{
			i++;
			}}
for(int l = 0; l < user.model[o].size(); l++){
				cout<<user.model[o][l];
			}
			cout<<": "<<curr<<endl;
		o++;
		}
	return;
}	
/*This is my creative milestone 6. 
This function finds all the strs that 
are present in the DNA strand, and then outputs that to
the user. It first checks if everything is loaded properly,
then calls on countAllSTR to do the work. 
*/
void findAllSTR(DNA user){
	if(user.database.size()==0){
		cout<<"No database loaded."<<endl;
		return;	}
	if(user.dna.size()==0){
		cout<<"No DNA loaded."<<endl;
		return;	}
	cout<<"Finding All DNA STR Instances..."<<endl;
	countAllSTR(user);
	return;
}

	/*This function is called to search to see whose dna it is
	It takes in the user DNA struct
	*/
void search(DNA user){
	//These next three if statements check if the 
	//Database, DNA, and process has happened
	//If not, we exit the function
	if(user.database.size()==0){
		cout<<"No database loaded."<<endl;
		return;
	}
	if(user.dna.size()==0){
		cout<<"No DNA loaded."<<endl;
		return;
	}
	if(user.strCount.size()==0){
		cout<<"No DNA processed."<<endl;
		return;
	}	
	cout<<"Searching database..."<<endl;
	//the i counter will be going through the 
	//datbase ourvector, 
	//k will go through each ourvector in the database ourvector
	//remember, database is a 2d ourvector
	for(int i = 0; i < user.database.size(); i++){
		string data;
		for(int k = 0; k < user.database[i].size(); k++){
			//we will put each character from the database[i]
			//ourvector into string data
			data += user.database[i][k];
		}
		//we will now use the stringstream function to get
		//the person's name. We did this with getLine
		stringstream s(data);
		string name;
		getline(s, name, ' ');
		//J will be going through strCount ourvector
		int j;
		for(j = 1; j < user.strCount.size(); j++){
			//value will take the person's str value
			int value;
			s>>value;
			//if the peron's value isn't equal to the str
			//count, we then break
			if(value != user.strCount[j]){
				break;
			}
		}
		//if j is equal to the strCount size
		//that means all the strs were equal
		//therefore, the dna was for said person
		//we then exit from the program
		if(j == user.strCount.size()){
			cout<<"Found in database!  DNA matches: "<<name<<endl;
			return;
		}
	}
	//if the program didn't leave the function,
	//that means we didn't find the person
	cout<<"Not found in database."<<endl;
}

int main() {
    //Over here, we have the beginning of the code
    // we initialize the DNA struct that will hold all the 
    //dna info for this program
    string userChoice;
    DNA user;
    cout<<"Welcome to the DNA Profiling Application."<<endl;
    cout<<"Enter command or # to exit: ";
    cin>> userChoice;
    //below is the menu for what the person can choose from
    while( userChoice != "#"){
    	if(userChoice == "load_db"){
    		string file;
    		cin>> file;
    		load_db(file, user);
    	}
    	else if(userChoice == "display"){
    		display(user);
    	}
    	else if(userChoice == "load_dna"){
    		string files;
    		cin >> files;
    		load_dna(files, user);
    	}
    	else if(userChoice == "process"){
    		process( user);
    	}
    	else if(userChoice == "search"){
    		search(user);
    	}
    	else if(userChoice == "all"){
    		findAllSTR(user);
    	}
    	cout<<"Enter command or # to exit: ";
    cin>> userChoice;
    }
	return 0;
}



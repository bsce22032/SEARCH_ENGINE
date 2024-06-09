#ifndef SETTINGS_H
#define  SETTINGS_H
#include <iostream>
#include <vector>
#include <cstdio>
#include <stack>
#include <fstream>
using namespace std;





class Settings {       //used singleton design pattern for this class
stack<string> history;

 Settings() {
    string data;
   ifstream file("history.txt");
    while(file>>data){
        history.push(data);

        

    }

 file.close();
 

 remove("history.txt");
    
 }


public:
   static Settings* instance;       
   static Settings* getInstance() {        //creating or returning the setting class instance
        if(!instance){
            instance=new Settings;
        }
        return instance;
    }

   


void errorhandling(){

}


void addhistory(string word) {
   history.push(word);
    
}

void display() {
    cout << "\nGetting history.....";
    cout << endl;
    cout << "\nHISTORY\n";
    string data;
    int num = 1;

stack<string >car=history;
while(!car.empty()){
    
    cout<<num++<<" : "<<car.top()<<endl;
    car.pop();
}

}

void savehistory(){



    ofstream file("history.txt");
    
    if(!file){
    
        cout<<"\nError Saving  the history\n";
        return ;
    }
   
    
  while(!history.empty()){
    file<<history.top()<<endl;
    history.pop();


  }
     file.close();
    }
  
   

};




#endif 
#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <iostream>
#include <unordered_map>
#include <fstream>
#include "settings.h"
#include  "searchAlgorithms.h"
#include  "Document.h"
using namespace std;


bool sortByNumOfViews(const Document& doc1, const Document& doc2) {
    return doc1.numofviews > doc2.numofviews;
}

void sortByPopularity(std::vector<Document>& arr) {
    sort(arr.begin(), arr.end(), sortByNumOfViews);
}


class searchEngine{
public:
searchAlgorithms prog; 
 TNode* root;
    unordered_map<string, Document> documentMap;
bool loaded;
Settings* car;                  //setting class
searchEngine(){
loaded=0;
car=Settings::getInstance();
    
}    

void printallDoc(){
    
 for(auto i:documentMap){

      i.second.display();
 }

}


    void addDocument(){              //this function is for adding a new document in your program
             ofstream file("files/filenames.txt", ios::app);
            cout << "File name: ";
            string name;
            cin >> name;
           
            file << endl << name;
            file.close();

            ofstream newfile("files/" + name+".txt");
            string content;
            cout << "Its content: ";
            cin.ignore(); 
            cin>>content;
            newfile << content;
            newfile<<"      ";
            newfile<<0;
            newfile.close();
       
    }

void loadDocuments(){            //this functions reads file names from filenames.txt opens them and put their data to hashmap
    double cara=0;
             ifstream file("files/filenames.txt");
    if (!file.is_open()) {
        cout << "Error opening filenames.txt" << endl;
      return;
    }
    int numofview;
    string name;
           while(file >> name) {
            file>>numofview;
        ifstream documentFile("files/" + name+".txt");
        if (!documentFile.is_open()) {
            cout << "Error opening file: " << name << endl;

            continue;     
        }

        vector<string> content;
        string word;
        while (documentFile >> word) {
            content.push_back(word);
        }

        documentMap[name] = Document(name, content);

        documentFile.close();
    }
          file.close();

}

void endprogram(){
    car->savehistory();
}

void  openaFile(const std::string& nameinp) {
    string filename = "files/filenames.txt";

    map<std::string, int> data;

    ifstream readFile("files/"+nameinp+".txt");
    if(!readFile){
        cout<<"\nFile Donot exsist\n";
        cout<<"\n..........\n";
        return;
    }
    ifstream file(filename);
    string name;
    int currentNumber;

    // Read data from the file into the map
    while (file>>name >>currentNumber) {
        // Increment the count for the specified name
        if (name==nameinp) {
            currentNumber++;
        }
        data[name]= currentNumber;
    }
    file.close();

    // Remove the file before opening it again
    
    ofstream outFile(filename);
    if(!outFile){
        cout<<"\nUnable to update view record......\n.....\n....... \n\n";
    }else{
    for (auto& entry:data) {
        
        outFile<<entry.first<<" "<<entry.second<<endl;
    }
    outFile.close();
    vector<string> content2;
    ifstream file2(nameinp);
    string data2;
    while(!file2.eof()){
        file2>>data2;
     cout<<data2<<" ";
content2.push_back(data2);
    }
    documentMap[nameinp].content=content2;

    file2.close();}
string datal;
    cout<<"\n_____________________________________________________\n";
    
    while(!readFile.eof()){
        readFile>>datal;
        cout<<datal<<" ";
    }
    cout<<"\n_____________________________________________________\n";
    return;








    
}


TNode* loadTrie(unordered_map<string, Document>& arr) {      // this function takes  names of the files from hashmap and creates tries of the file names letters
    TNode* root=new TNode();

    for (auto& pair:arr) {
        string title=pair.first;
        TNode* node=root;

        for (char c : title) {
            char lowerC=tolower(c);

            if (!node->child[lowerC]) {
                node->child[lowerC] = new TNode();
            }
            node = node->child[lowerC];
        }

        node->ew = 1;
        node->title = title;
    }

    return root;
}


vector<string> searchDocument(string keywords ){  //this is for searching a document it applies tfidf on keyword and search for trie for keyword and we get two vector combine them and return them
    car->addhistory(keywords);
   
    if(!loaded){
    root=loadTrie(documentMap);
    loadDocuments(); }
    vector<Document> res1;
    prog.searchTrie(root,keywords,documentMap,res1);
 
    vector<Document> res2=prog.TF_IDF(documentMap,keywords);
 
    
      vector<Document> result(res1);
   result.reserve(res1.size()+res2.size());
    for(auto i:res2){
        result.push_back(i);
    }
        
    sortByPopularity(result);
      vector<string> resultvec;
  string car="\0";
   for(auto i:result){
    if(car!=i.title){
     resultvec.push_back(i.title);}
     car=i.title;
   }


   return resultvec;

}





void searchwordinafile(string Keyword){      

  Document d;
   string st=Keyword;
   string name;

            Keyword[0] = tolower(Keyword[0]);
            st[0] = toupper(st[0]);

            d.extractFileName();
            string k1=Keyword+".";
            string k2=Keyword+"?";
            string k3=Keyword+"!";
            string k4=Keyword+",";
            string k5=Keyword+";";
            string k6=Keyword+"'";


            string c1=st+".";
            string c2=st+"?";
            string c3=st+"!";
            string c4=st+",";
            string c5=st+";";
            string c6=st+"'";
          
             bool b= true;
    cout<<"Enter name of File you want to search"<<endl;
cin>>name; d.check_Word_present_notPresent(name,Keyword,k1,k2,k3,k4,k5,k6,st,c1,c2,c3,c4,c5,c6); //  for single file
    d.counter_oneFile(name,Keyword,k1,k2,k3,k4,k5,k6,st,c1,c2,c3,c4,c5,c6);  //for one file
d.search_in_line(name,b,Keyword,k1,k2,k3,k4,k5,k6,st,c1,c2,c3,c4,c5,c6);            //       for all files

}



void searchinallfiles(string Keyword){
    
      Document d;
   string st=Keyword;

            Keyword[0] = tolower(Keyword[0]);
            st[0] = toupper(st[0]);

            d.extractFileName();
            string k1=Keyword+".";
            string k2=Keyword+"?";
            string k3=Keyword+"!";
            string k4=Keyword+",";
            string k5=Keyword+";";
            string k6=Keyword+"'";


            string c1=st+".";
            string c2=st+"?";
            string c3=st+"!";
            string c4=st+",";
            string c5=st+";";
            string c6=st+"'";
          
             bool b=false;
       string name;
 prog.check_Word_present_notPresent(d.vec,Keyword,k1,k2,k3,k4,k5,k6,st,c1,c2,c3,c4,c5,c6);//  for all files

    prog.counter_allFiles(d.vec,Keyword,k1,k2,k3,k4,k5,k6,st,c1,c2,c3,c4,c5,c6);        //  for all files


d.search_in_line(name,b,Keyword,k1,k2,k3,k4,k5,k6,st,c1,c2,c3,c4,c5,c6);            //       for all files


}

void display(){
    car->display();

}




};
#endif
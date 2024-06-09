#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMS_H

#include <iostream>
#include "Document.h"
#include<math.h>
#include <map>
#include <algorithm>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <vector>
using namespace std;




class TNode {
public:
    map<char, TNode*> child;                                               //    data members
    bool ew;
    string title;

    TNode(){
       ew=0;
    }
};


class searchAlgorithms{
   public:
void counter_allFiles(const vector<string> vec1,string Keyword,string k1,string k2,string k3,string k4,string k5,string k6,string st,string st1,string st2,string st3,string st4,string st5,string st6) {

    for (int i=0;i<vec1.size();i++) {                       //   loop so that every file is open one by one

        ifstream input("files/"+vec1[i]);

      if (!input.is_open()) {                                                           //  opening of file
            cout << "Error opening the file." << endl;
            return; // Return an error code
        }

        string s;
        int count = 0;
        while (input.eof() == 0) {                                                           //  if not open then generate error
            input >> s;
            if (s == Keyword || s == k1 || s == k2 || s == k3 || s == k4 || s == k5 || s == k6 || s == st || s == st1 ||
                s == st2 || s == st3 || s == st4 || s == st5 || s == st6) {
                count++;
            }
        }
        cout << "\nCount of key word is : " << count << " in " <<  vec1[i] << endl;
    }
}


    bool check_Word_present_notPresent(const vector<string> vec,string Keyword,string k1,string k2,string k3,string k4,string k5,string k6,string st,string st1,string st2,string st3,string st4,string st5,string st6) {
//                    ERROR HANDLING IN CASE OF UPPER CASE STRING
//                 commas condition excl sentence
        string n;
        for (int i = 0; i < vec.size(); i++) {
            bool found= false;
            ifstream input("files/" + vec[i]);                                              //  opening file

            if (!input.is_open()) {                                                              //  if not open then generate error
                cout << "Error opening the file." << endl;
                return false; // Return an error code
            }

            while(input.eof()==0){                                                                  //  loop that runs until the file end
                input>>n;
                if(n==Keyword||n==k1||n==k2||n==k3||n==k4||n==k5||n==k6||n==st||n==st1||n==st2||n==st3||n==st4||n==st5||n==st6){
                    cout<<"Exist in : "<<vec[i]<<endl;                                 //   condition to check word exist or not
                    found= true;
                    break;
                }

            }

            if(!found){                                               //    in case of word is not found
                cout<<"Not exist in : "<<vec[i]<<endl;
            }



        }
        return true;
    }

     


   


void sortfilnames(){
    
}



   
double TF(Document& arr, string keyword) {        //calculate difference of number of  words matching that keyword to total number of words
    int num = 0;
    if (arr.content.empty()) {
        return 0.0;
    }

    for ( auto& word : arr.content) {
        if (word == keyword) {
            num++;
        }
    }
    return static_cast<double>(num) / arr.content.size();
}


double IDF(unordered_map<string, Document>& arr, string keyword) {   //calculte  log of difference between number of doc dontaining that keyword and the total number of docs
    int numof = 0;
    int numofocc = 0;

    for (auto& i : arr) {
        bool test = false;
        for (auto j : i.second.content) {
            if (!test && j == keyword) {
                test = true;
                
                numofocc++;
            }
        }
        numof+=1;
      
    }

    if (numof == 0) {
       
        return 0.0;
    }
   double result=log(static_cast<double>(numofocc) / numof);

   
    if (isinf(result)&&result < 0) {
        return 0.0;
    }else return result;

}

            

vector<Document> TF_IDF(unordered_map<string, Document>& arr, string keyword) {
    vector<Document> files; 
    map<double,Document> car;
    double idf = IDF(arr, keyword);
    
    for (auto& pair : arr) {
        double num = TF(pair.second, keyword);
       
        double tfidf = num * idf;
        if(tfidf!=0){
            
            car[tfidf]=pair.second;
        }  }
           for(auto i:car){
          
            files.push_back(i.second);
         }

  
    return files;




}



void searchTrie(TNode* root, string query, unordered_map<string, Document>& documentMap, vector<Document>& result) {
    result.clear();

   
    transform(query.begin(), query.end(), query.begin(), ::tolower);

  
    TNode* node = root;
    for (char c : query) {
        char lowerC = tolower(c);
        if (!node->child[lowerC]) {
           
            return;
        }
        node = node->child[lowerC];
    }

    
    queue<TNode*> q;
    q.push(node);

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        if (current->ew) {
            string currTitle = current->title;
            auto it = documentMap.find(currTitle);

            if (it != documentMap.end()) {
                Document& doc = it->second;
                result.push_back(doc);
            }
        }

        for (auto& child : current->child) {
            q.push(child.second);
        }
    }
}




};

#endif
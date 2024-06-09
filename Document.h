#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <iostream>
#include <cctype>
#include <vector>
#include<string>
#include<fstream>
using namespace std;


class Node{
public:
    string data;
    Node*next;
    Node( string data){
        this->data=data;
        next= nullptr;
    }
};
class Document{
public:
string title;                  //title of the document
int numofviews;     // number of views a document had
vector<string> content;                                                //                   store words of file
vector<string> vec;  
Node*tail;
Node*head;

Document(string ti,vector<string> con){
    title=ti;
    content=con;
}
Document(){
    tail= nullptr;
    head= nullptr;
}
void extractFileName(){                                                         //   O(n)
    cout<<endl;
    string x;
    ifstream input("files/filenames.txt");

    if (!input.is_open()) {
        cout << "Error opening the file." << endl;
        return ; // Return an error code
    }
    int rub;
    while (input >> x) {
        input>>rub;
        x=x+".txt";
        vec.push_back(x);
    }
    cout<<endl;
input.close();
}
    bool check_Word_present_notPresent(string name,string Keyword,string k1,string k2,string k3,string k4,string k5,string k6,string st,string st1,string st2,string st3,string st4,string st5,string st6) {
//                    ERROR HANDLING IN CASE OF UPPER CASE STRING
//                 commas condition excl sentence
    string n;
    name=name+".txt";
            bool found= false;
            ifstream input("files/" + name );                                            //  opening file

            if (!input.is_open()) {                                                           //  if not open then generate error
                cout << "Error opening the file." << endl;
                return false; // Return an error code
            }

            while(input.eof()==0){                                                             //  loop that runs until the file end
                input>>n;
                if(n==Keyword||n==k1||n==k2||n==k3||n==k4||n==k5||n==k6||n==st||n==st1||n==st2||n==st3||n==st4||n==st5||n==st6){
                    cout<<"Exist in : "<<name<<endl;           //   condition to check word exist or not
                    found= true;
                    break;
                }

            }

            if(!found){                                          //    in case of word is not found
                cout<<"Not exist in : "<<name<<endl;
            }




        return true;
    }




    void search_in_line(string name,bool b,string key,string k1,string k2,string k3,string k4,string k5,string k6,string s,string st1,string st2,string st3,string st4,string st5,string st6) {
    string st;
    int x=0;

        if(b==1){
        name=name+".txt";
        for(int i=0;i<vec.size();i++){              //   loop so that every file is open one by one
            if(name==vec[i]){
                x=1;
                vec.clear();
                vec.shrink_to_fit();
                vec.push_back(name);
                break;
            }

        }
        if(x==0){
            cout<<"File "<<name<<" does not exist"<<endl;
            vec.clear();
            vec.shrink_to_fit();
        }
    }
        for (int i = 0; i < vec.size(); i++) {              //   loop so that every file is open one by one

            ifstream input("files/" + vec[i]);



            if (!input.is_open()) {                         //     check file open or not
                cout << "Error opening the file." << endl;
                return ; // Return an error code
            }

            while(input.eof()==0){                            //   run until the file end
                input>>st;
                list_insertion(st);
                int x=(st.length())-1;
                if(st[x]=='.'){
                    line_checker(key,i, k1, k2,k3, k4,k5, k6, s, st1, st2, st3, st4,st5,st6);
                }

            }

        }
//        delete_list();
    }
    void list_insertion(string st){                                      //  insertion in list
    if(tail==nullptr||head== nullptr){
        Node*node1=new Node(st);
        tail=node1;
        head=node1;
        return;
    }
    Node*node2=new Node(st);
    tail->next=node2;
    tail=node2;
}
void display(){                                       //   display line that carry the word
    Node*temp=head;
    while(temp!= nullptr){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}
void line_checker(string key,int i,string k1,string k2,string k3,string k4,string k5,string k6,string st,string st1,string st2,string st3,string st4,string st5,string st6){
    Node*temp=head;
    while(temp!= nullptr){                                          //    loop that run until the list end
        if(key==temp->data||k1==temp->data||k2==temp->data||k3==temp->data||k4==temp->data||k5==temp->data||k6==temp->data||st==temp->data||st1==temp->data||st2==temp->data||st3==temp->data||st4==temp->data||st5==temp->data||st6==temp->data){
            cout<<endl;                                                          //    check word is present in list or not
            cout<<"File name : "<<vec[i]<<endl;
            cout<<endl;
            display();                                  //    display function to print line
            delete_list();                             //   after display the line delete it form list to make it empty
            return;
        }
        temp=temp->next;
    }
    delete_list();

}
void delete_list(){                                                                //    deleting list
    while (head!=nullptr) {
        Node* temp=head;
        head=head->next;
        delete temp;
    }
    head= nullptr;
    tail= nullptr;
}

void counter_oneFile(string nameOfFile,string Keyword,string k1,string k2,string k3,string k4,string k5,string k6,string st,string st1,string st2,string st3,string st4,string st5,string st6){
    ifstream input("files/"+nameOfFile+".txt");                          //   opening of file

    if (!input.is_open()) {                                                           //  if not open then generate error
        cout << "Error opening the file." << endl;
        return ; // Return an error code
    }

    string s;
    int count=0;
    while(input.eof()==0){                                      //    loop that run until file end
        input>>s;
        if(s==Keyword||s==k1||s==k2||s==k3||s==k4||s==k5||s==k6||s==st||s==st1||s==st2||s==st3||s==st4||s==st5||s==st6){
            count++;                        //    increment count value
        }
    }
    cout<<"\nCount of key word is : "<<count<<" in "<<nameOfFile+".txt"<<endl;        //   display count of word
}
};
#endif
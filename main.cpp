#include <iostream>
#include <fstream>
#include  "searchEngine.h"

#include "settings.h"

using namespace std;

Settings *Settings::instance = NULL;


int main() {
    searchEngine *sengine;
    sengine = new searchEngine();

    char inp;
    while (inp != 'e') {
        cout<<endl;
        cout<<"Options in File Search Engine"<<endl;
        cout<< " \n1:Search for a file\n2:Open A File\n3:Search in a File \n4:Setting\ne:Exit";
        cout<<"\nEnter option : ";
        cin >> inp;
        sengine->loadDocuments();
        if (inp == '1') {
            string words;
            cout << "\nEnter context";
            cin >> words;
            
            vector <string> data = sengine->searchDocument(words);
            cout << "\nHere are the following search result ........\n";
            for (auto i: data) {
                cout << i << ".txt" << endl;
            }
            cout << "\n.......";
        }else if(inp=='2'){
            cout<<"\nEnter file name";
            string name;
            cin>>name;
            sengine->openaFile(name);
        } else if (inp == '3') {
//        cout<<"\nEnter word";
//        string word;
//        cin>>word;
//
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;
            Document d;

            int choice;
            searchAlgorithms s;
            string Keyword;
            bool b = false;
            cout << "Enter name of key word you want to search " << endl;
            cin >> Keyword;

            string st = Keyword;

            Keyword[0] = tolower(Keyword[0]);
            st[0] = toupper(st[0]);


            d.extractFileName();                                           //     all files names enter in a vector
            string k1 = Keyword + ".";                                       //     wrong search  condition handle
            string k2 = Keyword + "?";                                      //     wrong search  condition handle
            string k3 = Keyword + "!";                                      //     wrong search  condition handle
            string k4 = Keyword + ",";                                      //     wrong search  condition handle
            string k5 = Keyword + ";";                                      //     wrong search  condition handle
            string k6 = Keyword + "'";                                      //     wrong search  condition handle

            string c1 = st + ".";                                      //     wrong search  condition handle
            string c2 = st + "?";                                      //     wrong search  condition handle
            string c3 = st + "!";                                      //     wrong search  condition handle
            string c4 = st + ",";                                      //     wrong search  condition handle
            string c5 = st + ";";                                      //     wrong search  condition handle
            string c6 = st + "'";                                      //     wrong search  condition handle
            string name;
            cout << "Enter 1 if you want to search in 1 file" << endl;
            cout << "Enter 2 if you want to search in all files" << endl;
            //                                    ask user to search in one or all files
            cin >> choice;
            if (choice == 1) {
                b = true;
                cout << "Enter name of File you want to search" << endl;
                cin >> name;
                d.check_Word_present_notPresent(name, Keyword, k1, k2, k3, k4, k5, k6, st, c1, c2, c3, c4, c5,
                                                c6); //  for single file
                d.counter_oneFile(name, Keyword, k1, k2, k3, k4, k5, k6, st, c1, c2, c3, c4, c5, c6);  //for one file
            }
            if (choice == 2) {
                s.check_Word_present_notPresent(d.vec, Keyword, k1, k2, k3, k4, k5, k6, st, c1, c2, c3, c4, c5,
                                                c6);//  for all files
                s.counter_allFiles(d.vec, Keyword, k1, k2, k3, k4, k5, k6, st, c1, c2, c3, c4, c5,
                                   c6);        //  for all files
            }
            d.search_in_line(name, b, Keyword, k1, k2, k3, k4, k5, k6, st, c1, c2, c3, c4, c5,
                             c6);            //       for all files


        }  else if (inp == '4') {

            cout << "\nDisplay history of\n1:Searches";
            int in;
            cin >> in;

            if (in == 1) {
                sengine->display();

            }


        } else if(inp=='e'){
            sengine->endprogram();
        }

    }


}



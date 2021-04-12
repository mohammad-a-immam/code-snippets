//********SETUP*********//
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;
//*********//

//************PROTOTYPES************//
//stringstream LoadFIle(string fileName);

int main() {

    //MY DECLARABLES//

    map<string, int> words;
    int totalWordCount=0;
    auto mapIterator = words.begin();

    cout << "Select a file to open (1-4)" << endl;
    int option;
    cin >> option;
    string filename = "ipsum";
    filename.append(to_string(option));
    filename.append(".txt");

    ////LOAD THE FILE////

    ifstream inputStream(filename);
    if (inputStream.is_open()) {
        //DECLARABLES
        string theFileLine;
        string stringToStore;
        stringstream strstream(theFileLine);

        bool first=true;
        bool matched=false;

        while (!inputStream.eof()) {
            getline(inputStream, theFileLine);   //Reads the whole line in a string
            stringstream strstream(theFileLine);
            mapIterator = words.begin();
            //map<string, int> words;
            string a = "";
            while (getline(strstream, stringToStore, ' ')) {
                matched = false;
                a = "";
                for (unsigned int i = 0; i < stringToStore.size(); i++) {

                    if((stringToStore[i] >= 'A' && stringToStore[i] <= 'Z') ||(stringToStore[i] >= 'a' && stringToStore[i] <= 'z')){

                        a +=  tolower(stringToStore[i]);
                    }
//                    if ((stringToStore[i] < 65) || ((stringToStore[i] >= 91) && (stringToStore[i] <= 96)) ||
//                        (stringToStore[i] > 122))
//                    {
//                        stringToStore.erase(i);
//                        increaseI= false;
//                    }
//                    if ((stringToStore[i] >= 65) & (stringToStore[i] <= 90))
//                        stringToStore[i] = tolower(stringToStore[i]);
//
//                    if (increaseI)
//                    {
//                        i++;
//                    }
                }
                stringToStore = a;

                //****ADD IT TO THE MAP IF IT DOESNT EXIST*****/

                for (mapIterator = words.begin(); mapIterator != words.end(); mapIterator++) {

                    if (mapIterator->first == stringToStore)
                    {
                        words[stringToStore]++;
                        matched = true;
                        break;
                    }
                }

                if (!matched&!first&(stringToStore.size()>0))
                {
                    words[stringToStore] = 1;
                    totalWordCount++;
                }

                if (first&(stringToStore.size()>0)) {
                    words[stringToStore] = 1;
                    first = false;
                    totalWordCount++;
                }
            }
        }
        inputStream.close();
    }

    else
        cout<<"File Not Found!"<<endl;

    cout<<"File name: "<<filename<<endl;
    cout << "Choose an operation: " << endl;

    cout << "1. Display word list" << endl;
    cout << "2. Most common word" << endl;
    cout << "3. Words longer than (X) characters" << endl;
    cout << "4. Search for a particular word (ignore case!)" << endl;

    cin >> option;
    if (option == 1)
    {
        //**CHECK**//
        for (mapIterator=words.begin(); mapIterator != words.end(); mapIterator++) {
            cout << (*mapIterator).first << " ";
            cout  << mapIterator->second << endl;
        }

        cout<<"Word count: "<<totalWordCount;
    }
    else if (option == 2)
    {
        string mostCommonString="NF";
        int highest=words.begin()->second;            //integer for highest
        //**CHECK**//
        for (mapIterator=words.begin(); mapIterator != words.end(); mapIterator++) {
            if(highest<(mapIterator->second))
            {
                highest=mapIterator->second;
                mostCommonString=mapIterator->first;
                //break;
            }
        }
        for (mapIterator=words.begin();mapIterator!=words.end();mapIterator++)
        {
            if (highest==mapIterator->second)
            {
                cout<<"Most commonly used word: "<<mapIterator->first<<" "<<mapIterator->second<<endl;
                break;
            }
        }
    }
    else if (option == 3)
    {
        unsigned int length;
        cin>>length;

        vector<string> longerThanXStrings;

        //integer for highest
        //**CHECK**//
        for (mapIterator=words.begin(); mapIterator != words.end(); mapIterator++) {
            if((mapIterator->first).size()>length)
            {
                longerThanXStrings.push_back(mapIterator->first);
            }
        }

        cout<<"Words longer than "<<length<<": ";

        for (unsigned int i=0;i<longerThanXStrings.size();i++)
        {
            cout<<longerThanXStrings[i]<<endl;
        }

    }
    else if (option == 4)
    {
        string search;
        cin>>search;

        for (unsigned int i=0;i<search.size();i++)
        {
            if ((search[i] >= 65) & (search[i] <= 90))
                search[i] = tolower(search[i]);
        }

        int foundCount=0;
        for (mapIterator=words.begin();mapIterator!=words.end();mapIterator++)
        {
            if ((mapIterator->first)==search)
            {
                foundCount=mapIterator->second;
                break;
            }
        }

        cout<<search<<" found in file "<<foundCount<<" times.";
    }

    return 0;
}
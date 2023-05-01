/*
Name: Marlon Alejandro, 5002573038, Assignment 5
Description: Spell Checker 
Input: Text file
Output: Suggested words
*/
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <vector>

using namespace std;

vector<string> replaceLetter(string word);
vector<string> spellCheck(vector<string> word, unordered_map<string, bool>& dictionary);
bool contains(string str1, unordered_map<string, bool>& dictionary);
void ReadDictionary(unordered_map<string, bool>& dictionary, ifstream& file);
void ReadPassage(unordered_map<string, bool>& dictionary, vector<string>& errors, ifstream& file);
void RemoveDups(vector<string>& errors);
void Suggestions(unordered_map<string, bool>& dictionary, vector<string>& errors);

int main()
{   
    ifstream file;
    string spellCheck; 
    unordered_map<string, bool> dictionary;
    vector<string> errors; 
    ReadDictionary(dictionary, file);         // read in dictionary file into unordered map
    ReadPassage(dictionary, errors, file);    // read in text file into vector
    RemoveDups(errors);                         // remove any duplicate entries
    Suggestions(dictionary, errors);            // provide suggested words
    
    return 0; 
}

void ReadDictionary(unordered_map<string, bool>& dictionary, ifstream& file){
    string entry;
    file.open(("usa.txt")); 
    while(!file.eof()){
        file>>entry; 
        dictionary.insert({entry, true}); // true is arbitrary
    }
    file.close(); 
}

void ReadPassage(unordered_map<string, bool>& dictionary, vector<string>& errors, ifstream& file){
    string fileName;
    string spellCheck;

    cout<<"Enter filename: \n"; 
    cin >> fileName; 
    file.open(fileName); 

    while (!file.eof()){
        file >> spellCheck;
        //change text to lower case to make a consistent comparison (usa.txt is alread in lower case)
        transform(spellCheck.begin(),spellCheck.end(),spellCheck.begin(),::tolower);    

        if(dictionary.find(spellCheck) == dictionary.end()){
            //Mispelled words willbe displayed in Uppercase
            transform(spellCheck.begin(),spellCheck.end(),spellCheck.begin(),::toupper);
            errors.push_back(spellCheck); 
        } 
    }

    file.close();

}
void RemoveDups(vector<string>& errors){
    // vector<string>::iterator it;
    // sort(errors.begin(), errors.end());
    // it = unique(errors.begin(), errors.end());              
    // errors.resize(distance(errors.begin(),it));

    string word;

    for (vector<string>::iterator it = errors.begin(); it < errors.end(); it++){
        word = *it;
        for (vector<string>::iterator it2 = it+1; it2<errors.end(); it2++){
                if (word == *it2){
                    errors.erase(it2);
                }
        }
    }
}


void Suggestions(unordered_map<string, bool>& dictionary, vector<string>& errors){
    for(string mispelled : errors){
        vector<string> valid;
        cout<< mispelled <<" is misspelled\n\n"; 
        valid=spellCheck(replaceLetter(mispelled), dictionary);   
    }
}

vector<string> replaceLetter(string word)
{
    vector<string> result; 
    string String = word;
    int a;
    int z;
    char insert;

    transform(String.begin(),String.end(),String.begin(),::tolower);

    //replace each word with A-Z
    for(int i =0; i<=word.length()-1; ++i){
        a = 97; //ascii a 
        z = 122; //ascii z         
        while(a <= z){
                word = String; 
                word.erase(word.begin()+i);
                word.insert(word.begin()+i, 1, a);
                result.push_back(word);
                a++;
        }
    }
    //insert A-Z between each letter
    for(auto i = word.begin(); i<=word.end(); ++i){
        word=String;
        a =97;
        while(a <= z) {
                word.insert(i,a);
                result.push_back(word); 
                word.erase(i);
                a++;
        }
    }

    return result; 
}

vector<string> spellCheck(vector<string> word, unordered_map<string, bool>& dictionary){
    
        vector<string> valid;
        
        //if word is found in our dictionary push to our valid string vector
        for (vector<string>::iterator String=word.begin(); String<= word.end();String++)
            if(!(dictionary.find(*String) == dictionary.end())) {
                valid.push_back(*String); 
            }
    
        sort(valid.begin(), valid.end());

        //if no suggested word exists in out dictionary, prompt user

        if(valid.empty()){
            cout << "No suggestions\n";
        }
        //print suggested strings
        else{
            cout <<"Suggested words\n";
            for (vector<string>::iterator String=valid.begin(); String< valid.end();String++){
                string String2=*String;
                for(int i=0; i<=String2.length()-1; i++){
                    String2[i]=toupper(String2[i]);
                }
                cout<< String2 << endl;
            }
        }
       
        cout<< endl;

    return valid;    
  
}

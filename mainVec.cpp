/*
Name: Marlon Alejandro, 5002573038, Assignment 5
Description: Spell Checker 
Input: Text file
Output: Suggested words
*/
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

vector<string> replaceLetter(string word);
vector<string> spellCheck(vector<string> word, vector<string>& dictionary);
bool contains(string str1, vector<string>& dictionary);
void ReadDictionary(vector<string>& dictionary, ifstream& file);
void ReadPassage(vector<string>& dictionary, vector<string>& errors, ifstream& file);
void RemoveDups(vector<string>& errors);
void Suggestions(vector<string>& dictionary, vector<string>& errors);

int main()
{   
    ifstream file;
    string spellCheck; 
    vector<string> dictionary; 
    vector<string> errors; 
    ReadDictionary(dictionary, file);         // read in dictionary file into unordered map
    ReadPassage(dictionary, errors, file);    // read in text file into vector
    RemoveDups(errors);                         // remove any duplicate entries
    Suggestions(dictionary, errors);            // provide suggested words
    
    return 0; 
}

void ReadDictionary(vector<string>& dictionary, ifstream& file){
    string entry;
    file.open(("usa.txt")); 
    while(!file.eof()){
        file>>entry; 
        dictionary.push_back(entry); 
    }
    file.close(); 

}

void ReadPassage(vector<string>& dictionary, vector<string>& errors, ifstream& file){
    string fileName;
    string spellCheck;

    cout<<"Enter filename: \n"; 
    cin >> fileName; 
    file.open(fileName); 

    while (!file.eof()){
        file >> spellCheck;
        transform(spellCheck.begin(),spellCheck.end(),spellCheck.begin(),::tolower);
        if(std::find(dictionary.begin(), dictionary.end(), spellCheck) == dictionary.end()){
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

    for (auto it = errors.begin(); it < errors.end(); it++){
        word = *it;
        for (auto it2 = it+1; it2<errors.end(); it2++){
                if (word == *it2){
                    errors.erase(it2);
                }
        }
    }
}

void Suggestions(vector<string>& dictionary, vector<string>& errors){
    for(auto mispelled : errors){
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

vector<string> spellCheck(vector<string> word, vector<string>& dictionary){
    
        vector<string> valid;
        
        //if word is found in our dictionary push to our valid string vector
        for (auto String=word.begin(); String<= word.end();String++)
            if(find(dictionary.begin(),dictionary.end(), *String) != dictionary.end()) {
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

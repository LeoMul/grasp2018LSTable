#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <stdio.h>
using namespace std;
#define COUNT (4*1024*1024)             // number of values to sort



vector<string> ParseLine(string line_c){
    vector<string> TextArray;
    string s;

    //cout <<line_c;
    const char *line = line_c.c_str();
    int i = 0;
    char separator = ' ';

    while (i < strlen(line)) {
        if (line[i] != separator) {
            s += line[i]; 
        } else {

            if (s!=""){
                TextArray.push_back(s);
            }
            s.clear();
        }
        i++;
    }

    if (s!=""){
        TextArray.push_back(s);
    }

    return TextArray;
}


void SpitOut(string filename){

  string myText;
  ifstream MyFile(filename);

  while (getline (MyFile, myText)) {
  // Output the text from the file
    cout << myText << "\n";
  }
  MyFile.close();

}
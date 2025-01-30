#include "readJJ.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <stdio.h>
#include "Eigenstate.cpp"
#include "sort.cpp"
#include "read_utils.cpp"
using namespace std;
#define COUNT (4*1024*1024)             // number of values to sort




void parsejjJFile(const char* filename){

    //Need to parse two files, 
    //(name).sum (input)
    //rcsf.inp (assumed )

    //(name).sum as energy levels and (most of the) eigenvectors.
    //assume rcsf.inp is sorted into J,Pi blocks 
    //which appears to always be the case.
    //Note that we can have a different number of eigenvectors
    // than csfs.

    //Should account for this in the dimension set.
    //Although setting the dimensions as the number
    //of rcsfs is going to be more than that anyway. 

    //First step, read in the rcsfs. 

    //there should be number_of_blocks elements in rcsf_labels and jjJ_labels
    //each of which are themselves a vector of number_in_each_block strings.
    
    //we might want to store the parity as well, should probably be taken care of when we parse
    //the sum file though. 

    size_t number_of_blocks;
    vector <size_t> number_in_each_block;
    vector<vector <string> > rcsf_labels; 
    vector<vector <string> > jjJ_labels; 
    
    vector<string> TextArray;
    string rcsfinp = filename;
    ifstream File(rcsfinp);
    string Text;
    string rcsf;
    string jjLabel;
    string JPi;

    bool check = true; 

    while(check){ 
        getline (File, Text,'\n');
        TextArray = ParseLine(Text);
        for(int i=0;i<TextArray.size();i++){
            cout << TextArray[i] << " "; 
        }
        cout << "\n";
        if (TextArray.size() == 1){
            check = false;
        }
    }
    jjEigenlabel dummytuple;
    dummytuple = getJJcsf(File);
    dummytuple = getJJcsf(File);
    dummytuple = getJJcsf(File);
    dummytuple = getJJcsf(File);

    check = true;
    int peekint;
    char peekchar;


    while((check)){

        streampos oldpos = File.tellg();  // stores the position
        getline (File, Text,'\n');
        //cout << Text << "\n";

        if(File.eof()){
            break;
        };

        TextArray = ParseLine(Text);
        //cout << TextArray[0] << "hello";
        for(int ii=0;ii<TextArray.size();ii++){
            cout << TextArray[ii];
        }
        cout << "\n";
        if(TextArray[0] == "*"){
            printf("new block\n");
            
        }
        else{
            File.seekg (oldpos);
            dummytuple = getJJcsf(File);
        };

        //cout << Text << "\n";
        //File.seekg (oldpos);   // get back to the position         
        //getline (File, Text,'\n');
        //cout << Text << "\n";

        //cout << Text << "\n";
        //if (peekint > -1){ 
        //    peekchar = char(peekint);
        //    printf("%c\n",peekchar);
        //    if (peekchar =='*'){check = false;};
        //    dummytuple = getJJcsf(File);
        //}
        
    }



}


jjEigenlabel getJJcsf(ifstream &File){
    string Text;
    getline (File, Text,'\n');
    string rcsf = Text;
    string jjlabel;
    vector<string> TextArray;
    vector<string> returnarray;

    vector<string> jjArray;
    getline (File, Text,'\n');
    jjArray = ParseLine(Text);




    getline (File, Text,'\n');
    TextArray = ParseLine(Text);
    //for(int i=0;i<TextArray.size();i++){
    //    cout << TextArray[i] << " "; 
    //}
    //cout << TextArray[TextArray.size()-1];
    //cout<< "\n";
    string JPi = TextArray[TextArray.size()-1];


    int jjArraySize = jjArray.size();
    if (TextArray.size() > 1){
        jjArray[jjArraySize-2] = TextArray[TextArray.size()-2];
    }
    if (jjArraySize > 0 ){
        jjlabel = "("+jjArray[jjArraySize-2]+","+jjArray[jjArraySize-1]+")";
    }
    else{
        jjlabel = "(0,0)";
    }
    //for(int i=0;i<TextArray.size();i++){
    
    //cout << rcsf << " " << jjlabel<< " " << JPi <<  "\n"<< flush; 
    //}
    returnarray.push_back(rcsf);
    returnarray.push_back(jjlabel);
    returnarray.push_back(JPi);
    jjEigenlabel this_state = jjEigenlabel(rcsf,jjlabel,JPi);
    //tuple<string> returnvariable = (rcsf,jjlabel,JPi);
    return jjEigenlabel(rcsf,jjlabel,JPi);
}


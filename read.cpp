#include "read.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <stdio.h>
#include "Eigenstate.cpp"
#include "sort.cpp"
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
    string rcsfinp = "rcsf.inp";
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


    while((check)&&(!File.eof())){

        streampos oldpos = File.tellg();  // stores the position
        getline (File, Text,'\n');
        //cout << Text << "\n";

        if(File.eof()){
            break;
        };

        TextArray = ParseLine(Text);
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
    
    cout << rcsf << " " << jjlabel<< " " << JPi <<  "\n"<< flush; 
    //}
    returnarray.push_back(rcsf);
    returnarray.push_back(jjlabel);
    returnarray.push_back(JPi);
    jjEigenlabel this_state = jjEigenlabel(rcsf,jjlabel,JPi);
    //tuple<string> returnvariable = (rcsf,jjlabel,JPi);
    return jjEigenlabel(rcsf,jjlabel,JPi);
}

void parseLSJFile(const char* filename){
    string Text;
    string Delimit = " ";
    vector<string> TextArray;
    ifstream File(filename);
    getline (File, Text,'\n');
    //cout << Text << '\n';
    vector<int> positions;
    int pos;
    int JMOM;
    char parity;
    double energy;
    float percent;
    char lll;
    int count = 0;
   //getline (File, Text,'\n');
   //const char *line = Text.c_str();

   getline (File, Text,'\n');

   TextArray = ParseLine(Text);
   pos    = stoi(TextArray[0]);
   JMOM   = stoi(TextArray[1]);
   parity = TextArray[2].c_str()[0];
   energy = stod(TextArray[3]);
   
   vector<string> expansion_csfs;
   vector<double> expansion_coef;
   double  * energies = (double *)  malloc(COUNT*sizeof(double));
   size_t * I = (size_t *) malloc(COUNT*sizeof(size_t));

   vector<Eigenstate> Eigenstates;
   bool inEingstate = false;

   int max_length = 0;
 
   while(!File.eof()){  
       getline (File, Text,'\n');
       TextArray = ParseLine(Text);
       
       if (TextArray.size() == 3){
        //in an eigenstate 
        expansion_coef.push_back(stod(TextArray[1]));
        expansion_csfs.push_back(TextArray[2]);
       }

       if (TextArray.size() == 5){
        //new eigenstate
           Eigenstate prev_eigen_state = Eigenstate(energy,JMOM,parity,expansion_coef,expansion_csfs);
           Eigenstates.push_back(prev_eigen_state);
           for(int jj = 0; jj< expansion_csfs.size(); jj++){
                if( expansion_csfs[jj].size() > max_length){
                    max_length = expansion_csfs[jj].size();
                }
           }

           expansion_coef.clear();
           expansion_csfs.clear();
           positions.push_back(pos);
           energies[count] = energy;
           count++;
           if (count >= COUNT-1){
                cout << 'overflow in COUNT variable - you need to code this better Leo. \n';
           }
           pos    = stoi(TextArray[0]);
           JMOM   = stoi(TextArray[1]);
           parity = TextArray[2].c_str()[0];
           energy = stod(TextArray[3]);
       }
   }
        //this is ugly. i need to make this better.
        Eigenstate prev_eigen_state = Eigenstate(energy,JMOM,parity,expansion_coef,expansion_csfs);
        Eigenstates.push_back(prev_eigen_state);
        for(int jj = 0; jj< expansion_csfs.size(); jj++){
            if( expansion_csfs[jj].size() > max_length){
                max_length = expansion_csfs[jj].size();
            }
        }

        expansion_coef.clear();
        expansion_csfs.clear();
        positions.push_back(pos);
        energies[count] = energy;
        count++;

   // printf("%d",max_length);
    vector<size_t> indices;
    for (int kk = 0;kk<count;kk++) {
        I[kk] = kk;
    }
    argQuickSort(energies,I,0,count-1);

    double ground_energy = energies[I[0]];
    double energy_above_ground;
    size_t index;
    string header = "Level,  J, P,   Energy(Ry), ASF\n";
    printf("%s",header.c_str());
    for (int kk = 0;kk<count;kk++) {
        index = I[kk];
        Eigenstate state = Eigenstates[index];
        energy_above_ground = (state.energy - ground_energy)*2.0; 
        state.make_string(max_length);
        //cout << energy_above_ground << " ";
        //cout << state.parity;
        printf("%5d, %2d, %c, %12.9f, %s",kk+1,state.jmom,state.parity,energy_above_ground,state.expansion_string.c_str());
        cout << '\n';
    } 

    

    //quickSort(positions,0,positions.size()-1);
}

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
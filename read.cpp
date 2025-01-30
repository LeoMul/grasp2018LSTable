#include "read.h"
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


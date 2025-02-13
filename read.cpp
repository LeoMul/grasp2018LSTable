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
#include "adas.cpp"

using namespace std;
#define COUNT (4*1024*1024)             // number of values to sort

float decodeAngularMomentum(string jmomString){
    char twojArray[4];
    //cout << "hello"<<jmomString << '\n';
    //std::flush(std::cout);
    for (int ii =0;ii<jmomString.size();ii++){
        if(jmomString != "/"){
            twojArray[ii] = jmomString[ii];
        } else {
            //found a / -- return 2j/2 
            break;
            float j = atof(twojArray)*0.5;
            return j ;

        }
    }
    //else we found regular j
    float j = atof(twojArray);
    //std::cout << j << " "<< jmomString << '\n';
    return j;
}


void parseLSJFile(const char* filename,
                  vector<Eigenstate> &Eigenstates,
                   int &totalNumStates, int &max_length
                ){
    string Text;
    string Delimit = " ";
    vector<string> TextArray;
    ifstream File(filename);
    getline (File, Text,'\n');
    //cout << Text << '\n';
    vector<int> positions;
    int pos;
    float JMOM;
    char parity;
    double energy;
    float percent;
    char lll;
    int count = 0;


   getline (File, Text,'\n');

   TextArray = ParseLine(Text);
   pos    = stoi(TextArray[0]);
   //cout << "hello"<<TextArray[1] << '\n';
   //std::flush(std::cout);
   JMOM   = decodeAngularMomentum(TextArray[1]);


   string jstring = TextArray[1];

   parity = TextArray[2].c_str()[0];
   energy = stod(TextArray[3]);
   
   vector<string> expansion_csfs;
   vector<double> expansion_coef;
   double  * energies = (double *)  malloc(COUNT*sizeof(double));
   size_t * I = (size_t *) malloc(COUNT*sizeof(size_t));

   //vector<Eigenstate> Eigenstates;
   vector<Eigenstate> EigenStateCopy;
   bool inEingstate = false;

   max_length = 0;
   


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
                cout << "overflow in COUNT variable - you need to code this better Leo. \n";
           }
           pos    = stoi(TextArray[0]);

           JMOM   = decodeAngularMomentum(TextArray[1]);
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

    //Sort eigenstates again.. 
    double* energiesCopy = energies;
    EigenStateCopy = Eigenstates;   
    for(int ii=0;ii<Eigenstates.size();ii++){
        Eigenstates[ii] = EigenStateCopy[I[ii]];
        energies[ii] = energiesCopy[I[ii]];
    } 

    double ground_energy = energies[I[0]];
    double energy_above_ground;
    totalNumStates = count;

}

void displayLSJ(vector<Eigenstate> eigVector,int numPrint ,int totalNumStates, int max_length){
    size_t index;
    string header = "Level,  J, P,   Energy(Ry), ASF\n";

    int numberToPrint = totalNumStates; 
    if (numPrint != -1){ 
         numberToPrint = min(totalNumStates,numPrint);
    }

    double energy_above_ground; 
    double ground_energy = eigVector[0].energy;
    //printf("%d hello\n",numberToPrint);
    //std::flush(std::cout);
    printf("%s",header.c_str());

    for (int kk = 0;kk<numberToPrint;kk++) {
        Eigenstate state = eigVector[kk];
        energy_above_ground = (state.energy - ground_energy)*2.0; 
        state.make_string(max_length);
        printf("%5d, %4.1f, %c, %12.9f, %s",kk+1,state.jmom,state.parity,energy_above_ground,state.expansion_string.c_str());
        cout << '\n';
    } 
}
#include <filesystem>
namespace fs = std::filesystem;

bool fileExists(const std::string& filename) {
    return fs::exists(filename);
}

 void adas(vector<Eigenstate> Eigenstates,int numPrint ,int totalNumStates, int max_length){
     //int numberToPrint = numPrint;
    int numberToPrint = totalNumStates; 
    if (numPrint != -1){ 
         numberToPrint = min(totalNumStates,numPrint);
    }
     printf("&ADASEX NLEVS= %d NUMTMP=19 IRDTMP=1 ITCC=1 IBORN=0 IELAS=0 IEL='SYMBOL_HERE' FIPOT=0.0 IONTRM='TERM_HERE'/\n",numberToPrint);
     printf("1.00+03 1.50+03 1.80+03 2.00+03 2.50+03 5.00+03 7.50+03 1.00+04 1.50+04 1.80+04 2.00+04 3.00+04 4.00+04 5.00+04 6.00+04 7.00+04 8.00+04 9.00+04 1.00+05\n");
     
     //std::cout << numPrint << totalNumStates << max_length; 
     //std::flush(std::cout);
     



    size_t * I = (size_t *) malloc(totalNumStates*sizeof(size_t));
     for (int kk = 0;kk<totalNumStates;kk++) {
         I[kk] = size_t(kk);
     }



     double ground_energy = Eigenstates[0].energy;
     
     //need all the energies
     double * energies = (double *) malloc(totalNumStates*sizeof(double));

     for(int ii = 0;ii<totalNumStates; ii++){
        energies[ii] = Eigenstates[ii].energy-ground_energy;
     }
     double* energiesArray = &energies[0];
     
    if (fileExists("dstg3")){
    int numshifted = 0; 
    vector<double> shiftedEnergys;
    
    ifstream File("dstg3");
    vector<string> TextArray;
    string Text;
    for (int ii=0;ii < 5; ii++){
        getline (File, Text,'\n');
    }
    
    while(!File.eof()){
        getline (File, Text,'\n');
        TextArray = ParseLine(Text);
        //std::cout << TextArray[0] << "\n";
        numshifted++;
        //there has to be a better way 
        shiftedEnergys.push_back(atof(TextArray[0].c_str()));
     }

     for(int ii = 0;ii<numshifted; ii++){
        energies[ii] = shiftedEnergys[ii];
     }
     argQuickSort(energiesArray,I,0,totalNumStates-1);
     }

     //for (int kk = 0;kk<totalNumStates;kk++){
     //   std::cout<<I[kk] << "\n";
     //}


     double energy_above_ground; 
     size_t index;
     for (int kk = 0;kk<numberToPrint;kk++) {
         index = I[kk];
         //std::cout<<index << "\n";
         //std::flush(std::cout);
         Eigenstate state = Eigenstates[index];
         energy_above_ground = energiesArray[index]; ///(state.energy - ground_energy)*2.0; 

         state.make_string(max_length);
         state.make_string_adas(energy_above_ground,kk);
         cout << '\n';
     } 
 
     printf("NAME:\n");
     printf("DATE:\n");
     printf("\n");
     printf("\n");
     printf("\n");
     printf("                      ENTER DETAILS OF CALCULATION\n");                  
     printf("\n");
     printf("\n");
     printf("\n");
     printf("\n");
     printf(".\n");
 
 }


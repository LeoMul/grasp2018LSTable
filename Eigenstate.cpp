#include "Eigenstate.h"
#include <format>
#include <cstring>
using namespace std;

double ryd_to_cm = 109737.316;

char angDict[14] = "SPDFGHIKLMNOP";

int convertAngToNumber(char angLetter){
    //convert ang letter to a number 
    for (int ii =0; ii<13;ii++){
        if(angLetter==angDict[ii]){
            return ii;
        }
    }

    return 99;
}


void Eigenstate::make_string_adas(double ground_energy,int index){
    string adas_string = expansion_csfs[0]; 
    adas_string.erase(remove(adas_string.begin(), adas_string.end(), '('), adas_string.end()); //remove A from string
    adas_string.erase(remove(adas_string.begin(), adas_string.end(), ')'), adas_string.end()); //remove A from string
    //adas_string.erase(remove(adas_string.begin(), adas_string.end(), '.'), adas_string.end()); //remove A from string

    //printf(%12.9f.);

    double energy_above_ground = (energy - ground_energy)*2.0 * ryd_to_cm; 

    char * tab2 = new char [adas_string.length()+1];
    strcpy (tab2, adas_string.c_str());

    //General C/C++ malarky
    int angL = convertAngToNumber(tab2[strlen(tab2)-1]);
    char* x = &tab2[strlen(tab2)-2];
    int angS = atoi(x);

    std::replace( adas_string.end()-4, adas_string.end(), '_', '('); // replace all 'x' to 'y'
    adas_string = adas_string + ')';

    //take slice
    //make up to correct length

    string thisSlice = adas_string; 
    if (thisSlice.length()>= 13){
         thisSlice = adas_string.substr(adas_string.size()-13,adas_string.size()); 
    }

    if (thisSlice.length() < 13){
        for(int ii=0;ii<14-thisSlice.length();ii++){
            thisSlice = ' ' + thisSlice;
        }
    }

    //std::cout << thisSlice << '\n';
    //std::flush(std::cout);

    //char ctr[100] = adas_string.c_str();

    printf("%c%13s %4.1f %12.3f %4d",parity,thisSlice.c_str(),jmom,energy_above_ground,index+1);
    //printf(,adas_string.c_str(),energy_above_ground);




}

void slice(const char* str, char* result, size_t start, size_t end) {
    //https://stackoverflow.com/questions/26620388/c-substrings-c-string-slicing
    strncpy(result, str + start, end - start);
}



void Eigenstate::make_string(int max_length){
    size_t test = 3;
    size_t max_iter = min(test,expansion_coefficients.size());
    

    for (int ii = 0; ii < max_iter;ii++){ 
        string spaces = "";

        if (ii >0 ){expansion_string+="+ ";} 
        
        expansion_string += to_string(100.0*expansion_coefficients[ii]) +"% ";
        int diff = max_length - expansion_csfs[ii].size();
        for (int jj = 0; jj<diff;jj++){
            spaces += " ";
        }
        expansion_string += "["+spaces+expansion_csfs[ii]+"]" +" ";
    }
}

void Eigenstate::display(){

    string expansion_string = "";
    string format = "%15.8lf %s";
    
    for (int ii = 0; ii < 3;ii++){ 
        if (ii >0 ){expansion_string+="+ ";} 
        expansion_string += to_string(expansion_coefficients[ii]) +" ";
        expansion_string += "["+expansion_csfs[ii]+"]" +" ";
    }

    printf("%15.8lf %d %s\n",energy,jmom,expansion_string.c_str());
}
//
//Eigenstate::Eigenstate(
//            double energy,
//            int jmom,
//            char parity,
//            vector<double> expansion_coefficients,
//            vector<string> expansion_csfs
//        )
//        {
//          energy = energy;
//          jmom = jmom;
//          expansion_coefficients = expansion_coefficients;
//          expansion_csfs = expansion_csfs;
//        }


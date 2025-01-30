#include "Eigenstate.h"
#include <format>
using namespace std;

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


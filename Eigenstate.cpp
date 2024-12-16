#include "Eigenstate.h"
#include <format>
using namespace std;

void Eigenstate::make_string(){
    size_t test = 3;
    size_t max_iter = min(test,expansion_coefficients.size());
    for (int ii = 0; ii < max_iter;ii++){ 
        if (ii >0 ){expansion_string+="+ ";} 
        expansion_string += to_string(expansion_coefficients[ii]) +" ";
        expansion_string += "["+expansion_csfs[ii]+"]" +" ";
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


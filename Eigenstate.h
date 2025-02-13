#include <vector>
using namespace std;


class Eigenstate {
    public:
    //atributes;
        double energy;
        int jmom;
        char parity;
        vector<double> expansion_coefficients;
        vector<string> expansion_csfs;
        string expansion_string;
    //definition;
        Eigenstate(
            double energy_in,
            int jmom_in,
            char parity_in,
            vector<double> expansion_coefficients_in,
            vector<string> expansion_csfs_in
        ): energy(energy_in), 
           jmom(jmom_in),
           parity(parity_in),
           expansion_coefficients(expansion_coefficients_in),
           expansion_csfs(expansion_csfs_in) {}
    //print for now
        void display();
        void make_string(int max_length);
        void make_string_adas(double ground_energy,int index);
};
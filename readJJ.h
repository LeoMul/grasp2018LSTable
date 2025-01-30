#include <iostream>
#include <vector>
using namespace std;
//todo: put this in its own file, and also properly make a default constructor.

class jjEigenlabel{
    public:
        string rcsflabel;
        string jjJlabel;
        string JPi;
    jjEigenlabel(
        string rcsflabel_in,
        string jjJlabel_in,
        string JPi_in
    ): rcsflabel(rcsflabel_in),
       jjJlabel(jjJlabel_in),
       JPi(JPi_in) {}
    jjEigenlabel(){
        string rcsflabel="";
        string jjJlabel="";
        string JPi="";
    }
};

jjEigenlabel getJJcsf(ifstream &File); 
void parsejjJFile(const char* filename);

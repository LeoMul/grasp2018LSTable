#include <iostream>
#include <fstream>
#include "read.cpp"
#include "argparse.cpp"
//#include "Eigenstate.cpp"
#include <vector>

using namespace std;

void mainFunc(const char* filename, int num, bool adasbool){

    //Variables I need in all scopes
    vector<Eigenstate> Eigenstates;
    int totalNumStates;
    int maxLength;

    parseLSJFile(filename,Eigenstates,totalNumStates,maxLength);
    if (adasbool){
        adas(Eigenstates,num,totalNumStates,maxLength);

    } else{
      displayLSJ(Eigenstates,num,totalNumStates,maxLength);
    }

}

int main(int argc, char* argv[]) {
  bool adasbool = false;
  //If the user does not give me any information, print the help message.
  if(cmdOptionExists(argv, argv+argc, "-h"))
    {
        printHelp();
        return 0;
    }

  if(cmdOptionExists(argv, argv+argc, "-a"))
    {
      adasbool = true;
    }



  int num = -1; 
  if(cmdOptionExists(argv, argv+argc, "-n"))
    {   
        //ugly c++ code...
        char * numm = getCmdOption(argv, argv + argc, "-n");
        int length = strlen(numm); 
        char numAgain[length+1];

        strcpy(numAgain,numm);
        
        num = atoi(numAgain);


        //string file_path = "SeIII_000.lsj.lbl";

  }

  if(cmdOptionExists(argv, argv+argc, "-f"))
    {   
        char * file_path = getCmdOption(argv, argv + argc, "-f");
        //string file_path = "SeIII_000.lsj.lbl";
        //cout << file_path << "\n" ;
        mainFunc(file_path,num,adasbool);

    }
  else{
        //no file - no program.
        noFileError();
        return 0;
  }

  
  
  return 0;
}


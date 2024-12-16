#include <iostream>
#include <fstream>
#include "read.cpp"
#include "argparse.cpp"

using namespace std;

int main(int argc, char* argv[]) {
  
  //If the user does not give me any information, print the help message.
  if(cmdOptionExists(argv, argv+argc, "-h"))
    {
        printHelp();
        return 0;
    }

  if(cmdOptionExists(argv, argv+argc, "-f"))
    {   
        char * file_path = getCmdOption(argv, argv + argc, "-f");
        //string file_path = "SeIII_000.lsj.lbl";
        //cout << file_path << "\n" ;
        parseLSJFile(file_path);
    }
  else{
        //no file - no program.
        noFileError();
        return 0;
  }

  
  
  return 0;
}
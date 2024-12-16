#include <iostream>
using namespace std;
#include <algorithm>

void noFileError(){
    cout << "No file specified. Stopping. \n";
}

void printHelp(){
    cout << "Help message. to be implemented. \n";
}

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{   
    char ** itr = std::find(begin, end, option);

    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{   
    //checks for commands.
    return std::find(begin, end, option) != end;
}


/*
string_view get_option(
    const vector<string_view>& args, 
    const string_view& option_name) {
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == option_name)
            if (it + 1 != end)
                return *(it + 1);
    }
    
    return "";
}

bool has_option(
    const vector<string_view>& args, 
    const string_view& option_name) {
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == option_name)
            return true;
    }
    
    return false;
}*/
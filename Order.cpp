//**********************************************************************************
// Joshua Angel, joangel
// PA7
// Order.cpp
// Top-level client for the Dictionary ADT
//**********************************************************************************

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include<string>
#include <sstream>
#include <iterator>
#include <vector>
#include"Dictionary.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){
    //Ensure 2 arguments are provided
    if(argc != 3){
        fprintf(stderr, "Usage: Order <input file> <output file>\n");
        exit(1);
    }

    //Open the input file
    ifstream in;
    in.open(argv[1], ios::in);
    if(!in.is_open()){//If you can't open input file
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    //Open the output file
    ofstream out;
    out.open(argv[2], ios::trunc);
    if(!out.is_open()){//If you can't open outfile
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    int line_count;
    string line;

    //Read input file, place in dictionary
    Dictionary A;
    line_count = 0;
    while(getline(in, line))  {//Read and add values to dictionary
        line_count++;
        A.setValue(line, line_count);
    }

    //Print to outfile
    out << "" << A;
    out << "\n";
    out << "" << A.pre_string();
    out << "\n";

    in.close();
    out.close();
    return 0;
}
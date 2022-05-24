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

    //Open the output file
    ofstream out;
    out.open(argv[2], ios::trunc);


    int line_count;
    size_t begin, end, len;
    string line;
    string tokenBuffer;
    string token;
    string delim = " ";

// read each line of input file, place in dictionary
    Dictionary A;
    line_count = 0;
    while( getline(in, line) )  {
        line_count++;
        len = line.length();

        // get tokens in this line
        tokenBuffer = "";

        // get first token
        begin = min(line.find_first_not_of(delim, 0), len);
        end   = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end-begin);

        while( token!="" ){  // we have a token
            // update token buffer
            tokenBuffer += "   "+token;
            A.setValue(token, line_count);

            // get next token
            begin = min(line.find_first_not_of(delim, end+1), len);
            end   = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);
        }

    }



    if(out.is_open()){//Print to outfile
        out << "" << A;
        out << "\n";
        out << "" << A.pre_string();
        out << "\n";
    } else {
        cout << "Error: Unable to write to output file";
    }

    in.close();
    out.close();
    return 0;
}
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

    string line;
    string juice;
    if(in.is_open()){//Read from input file
        while(getline(in, line)){//Read line by line
                juice += line + " ";
        }
    } else {
        cout << "Error: Unable to open input file";
    }

    vector<string> words{};
    size_t position = 0;
    string space = " ";
    while((position = juice.find(space)) != string::npos){//Read in the words
        words.push_back(juice.substr(0, position));
        juice.erase(0, position + space.length());
    }

    int count = 1;
    Dictionary A;
    if(out.is_open()){
        for (const auto &str : words) {//Make the Dictionary
            A.setValue(str, count);
            count++;
        }
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
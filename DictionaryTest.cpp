//**********************************************************************************
// Joshua Angel, joangel
// PA7
// DictionaryTest.cpp
// A test client for the Dictionary ADT
//**********************************************************************************
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

    string S;
    int x;
    string s[] = {"one", "two", "foo", "bar", "happy", "is", "three", "par"};
    Dictionary A;
    Dictionary B;

    //SET VAL-------------------------------------------------------------------------------
    for(int i = 0; i < 8; i++){
        A.setValue(s[i], i+1);
    }

    B = A;
    //SIZE----------------------------------------------------------------------------------
    cout << "A SIZE: " << A.size() << endl;
    cout << A << endl;
    cout << "B SIZE: " << B.size() << endl;
    cout << B << endl;

    //CONTAINS------------------------------------------------------------------------------
    cout << "CONTAINS (one) : " << A.contains("one") << endl;
    cout << "CONTAINS (two): " << A.contains("two") << endl;
    cout << "CONTAINS(ohyeabb): " << A.contains("ohyeabb") << endl;
    cout << "CONTAINS(AYO?): " << A.contains("AYO?") << endl;
    cout << endl;

    //GET_VAL-------------------------------------------------------------------------------
    cout << "GetVal (one) : " << A.getValue("one") << endl;
    cout << "GetVal (two): " << A.getValue("two") << endl;
    cout << "GetVal (is): " << A.getValue("is") << endl;
    try{
        A.getValue("ohyeabb");
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    cout << endl;

    //BEGIN//HAS_CURRENT/CURRENT_KEY&VAL----------------------------------------------------
    cout << "Has Current: " << A.hasCurrent() << endl;
    A.begin();
    cout << "Beginning Current: " << A.hasCurrent() << endl;
    cout << "Current Key: " << A.currentKey() << endl;
    cout << "Current Val: " << A.currentVal() << endl;
    cout << endl;
    A.end();
    cout << "End Current: " << A.hasCurrent() << endl;
    cout << "Current Key: " << A.currentKey() << endl;
    cout << "Current Val: " << A.currentVal() << endl;
    cout << endl;

    //NEXT/PREV-----------------------------------------------------------------------------
    A.begin();
    A.next();
    cout << "Next Current: " << A.hasCurrent() << endl;
    cout << "Current Key: " << A.currentKey() << endl;
    cout << "Current Val: " << A.currentVal() << endl;
    cout << endl;

    //REMOVE--------------------------------------------------------------------------------
    A.remove("one");
    A.remove("bar");
    cout << "\nSIZE: " << A.size() << endl;
    cout << A << endl;

    //FORWARD-------------------------------------------------------------------------------
    for(B.begin(); B.hasCurrent(); B.next()){
        S = B.currentKey();
        x = B.currentVal();
        cout << "("+S+", " << x << ") ";
    }
    cout << endl << endl;


    //PREVIOUS------------------------------------------------------------------------------
    for(A.end(); A.hasCurrent(); A.prev()){
        S = A.currentKey();
        x = A.currentVal();
        cout << "("+S+", " << x << ") ";
    }
    cout << endl << endl;


    //PRE_STRING---------------------------------------------------------------------------
    cout << "pre_string:\n" << endl;
    B.pre_string();

    //EQUALS-------------------------------------------------------------------------------
    int first = A==B;
    cout << "A==B: " << first << endl;
    int second = (B==B);
    cout << "B==B: " << second << endl;
    Dictionary C = A;
    int third = A==C;
    cout << "A==C: " << third << endl;

    //CLEAR--------------------------------------------------------------------------------
    A.clear();
    cout << "\nSIZE: " << A.size() << endl;
    cout << A << endl;

    cout << endl;

    return( EXIT_SUCCESS );
}
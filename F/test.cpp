#include<iostream>
#include<fstream>
#include<cstring>
//#include"delim.cpp"
#include"person.h"
//#include"buffile.cpp"
using namespace std;

Person abhijit, anaya;

template <class IOB>
void testBuffer(IOB & Buff, char *myfile){
    Person p;
    int result;
    int recaddr1, recaddr2, recaddr3, recaddr4;
    ofstream TestOut(myfile, ios::out);
    result = Buff.WriteHeader(TestOut);
    cout << "write header " << result << endl;
    abhijit.Pack(Buff);
    recaddr1 = Buff.Write(TestOut);
    cout << "write at " << recaddr1 << endl;
    anaya.Pack(Buff);
    recaddr2 = Buff.Write(TestOut);
    cout << "write at " << recaddr2 << endl;
    TestOut.close();

    ifstream TestIn(myfile, ios::in);
    result = Buff.ReadHeader(TestIn);
    cout << "read header " << result << endl;
    p.Print(cout, "First record:");
    Buff.DRead(TestIn, recaddr2);
    p.Unpack(Buff);
    p.Print(cout, "Second record:");
    Buff.DRead(TestIn, recaddr1);
    p.Unpack(Buff);
}

void InitPerson(){
    cout << "Initializing 3 ppl" << endl;
    strcpy(abhijit.LastName, "taware");
    strcpy(abhijit.FirstName, "abhijit");
    strcpy(abhijit.Address, "dange");
    strcpy(abhijit.City, "pune");
    strcpy(abhijit.State, "ma");
    strcpy(abhijit.ZipCode, "33");
    abhijit.Print(cout);

    strcpy(anaya.LastName, "taware");
    strcpy(anaya.FirstName, "abhijit");
    strcpy(anaya.Address, "dange");
    strcpy(anaya.City, "pune");
    strcpy(anaya.State, "ma");
    strcpy(anaya.ZipCode, "33");
    anaya.Print(cout);
}

void testDelim(){
    cout << "\nTesting DelimTextBuffer" << endl;
    DelimFieldBuffer::SetDefaultDelim('|');
    DelimFieldBuffer Buff;
    Person::InitBuffer(Buff);
    testBuffer(Buff, "delim.dat");
}

int main(){
    testDelim();
    //testLenText();
    //testFixText();
    return 0;
}


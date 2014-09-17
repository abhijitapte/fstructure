#include<iostream>
#include"person.h"
using namespace std;

void Person::Print(ostream & stream, char *label){
    if(label==0) stream << "Person: ";
    else stream << label;
    stream << "Last Name '" << LastName << "'\n"
    << "First Name '" << FirstName << "'\n"
    << "Address '" << Address << "'\n"
    << "City '" << City << "'\n"
    << "State '" << State << "'\n"
    << "Zip Code '" << ZipCode << "'\n"
    << flush;
}

Person::Person(){
    Clear();
}

void Person::Clear(){
    LastName[0]=0;  FirstName[0]=0;
    Address[0]=0;   City[0]=0;
    State[0]=0;     ZipCode[0]=0;
}

int Person::Unpack(IOBuffer &Buffer){
    int numBytes;
    Clear();
    numBytes = Buffer.Unpack(LastName);
    LastName[numBytes] = 0;
    if(numBytes==-1) return 0;
    numBytes = Buffer.Unpack(FirstName);
    if(numBytes==-1) return 0;
    FirstName[numBytes] = 0;
    numBytes = Buffer.Unpack(Address);
    if(numBytes==-1) return 0;
    Address[numBytes] = 0;
    numBytes = Buffer.Unpack(City);
    if(numBytes==-1) return 0;
    City[numBytes] = 0;
    numBytes = Buffer.Unpack(State);
    if(numBytes==-1) return 0;
    State[numBytes] = 0;
    numBytes = Buffer.Unpack(ZipCode);
    if(numBytes==-1) return 0;
    ZipCode[numBytes] = 0;
    return 1;
}

int Person::Pack(IOBuffer &Buffer) const{
    int numBytes;
    Buffer.Clear();
    numBytes = Buffer.Pack(LastName);
    if(numBytes==-1) return 0;
    numBytes = Buffer.Pack(FirstName);
    if(numBytes==-1) return 0;
    numBytes = Buffer.Pack(Address);
    if(numBytes==-1) return 0;
    numBytes = Buffer.Pack(City);
    if(numBytes==-1) return 0;
    numBytes = Buffer.Pack(State);
    if(numBytes==-1) return 0;
    numBytes = Buffer.Pack(ZipCode);
    if(numBytes==-1) return 0;
    return 1;
}

int Person::InitBuffer(LengthFieldBuffer &Buffer){
    return 1;
}

/*
int Person::InitBuffer(DelimFieldBuffer &Buffer){
    return 1;
}
*/

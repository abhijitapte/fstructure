#include"person.h"
using namespace std;

void Person::Print(ostream & stream){
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

int Person::Unpack(LengthTextBuffer & Buffer){
    return 1;
}

int Person::Pack(LengthTextBuffer & Buffer){
    int result;
    Buffer.Clear();
    result = Buffer.Pack(LastName);
    result = result && Buffer.Pack(FirstName);
    result = result && Buffer.Pack(Address);
    result = result && Buffer.Pack(City);
    result = result && Buffer.Pack(State);
    result = result && Buffer.Pack(ZipCode);
    return result;
}


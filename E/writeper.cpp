#include<iostream>
#include"person.h"
using namespace std;

ostream & operator << (ostream & stream, Person &p){
    stream  << "Last Name '" << p.LastName << "'\n"
            << "First Name '" << p.FirstName << "'\n"
            << "Address '" << p.Address << "'\n"
            << "City '" << p.City << "'\n"
            << "State '" << p.State << "'\n"
            << "Zip Code '" << p.ZipCode << "'\n"
            << flush;
    return(stream);
}

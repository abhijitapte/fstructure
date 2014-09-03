using namespace std;

class Person{
    public:
        char LastName[16];
        char FirstName[16];
        char Address[16];
        char City[16];
        char State[3];
        char ZipCode[10];
        Person();
        void print();
};

void Person::print(){
    cout << "Last Name '" << LastName << "'\n"
    << "First Name '" << FirstName << "'\n"
    << "Address '" << Address << "'\n"
    << "City '" << City << "'\n"
    << "State '" << State << "'\n"
    << "Zip Code '" << ZipCode << "'\n"
    << flush;
}

Person::Person(){
    LastName[0]=0;
    FirstName[0]=0;
    Address[0]=0;
    City[0]=0;
    State[0]=0;
    ZipCode[0]=0;
}


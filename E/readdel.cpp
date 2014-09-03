#include<iostream>
#include<fstream>
#include<cstring>
#include"writeper.cpp"
using namespace std;

istream & operator >> (istream & stream, Person & p){
    char delim;
    stream.getline(p.LastName, 30, '|');
    if(strlen(p.LastName)==0) return stream;
    stream.getline(p.FirstName, 30, '|');
    stream.getline(p.Address, 30, '|');
    stream.getline(p.City, 30, '|');
    stream.getline(p.State, 15, '|');
    stream.getline(p.ZipCode, 10, '|');
    return(stream);
}

int main(){
    char filename[20];
    Person p;
    cout << "Enter file name: "<<flush;
    cin.getline(filename, 19);
    ifstream file (filename, ios::in);
    if(file.fail()){
        cout << "File open failed! " << filename << endl;
        return 0;
    }
    while(1){
        file >> p;
        if(strlen(p.LastName)==0) break;
        //p.print();
        cout << p;
    }
    return 0;
}


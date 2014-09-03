#include<fstream>
#include<cstring>
#include"readper.cpp"
using namespace std;

ostream & operator << (ostream & stream, Person &p){
    stream << p.LastName << p.FirstName << p.Address << p.City << p.State << p.ZipCode;
    return stream;
}

int main(){
    char filename[20];
    Person p;
    cout << "Enter file name : "<<flush;
    cin.getline(filename, 19);
    ofstream stream(filename, ios::out);
    if(stream.fail()){
        cout << "File open failed!" << endl;
        return 0;
    }

    while(1){
        cin >> p;
        if(strlen(p.LastName)==0) break;
        stream << p;
    }
}

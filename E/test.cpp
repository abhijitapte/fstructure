#include<fstream>
#include<cstring>
#include"lentext.cpp"
#include"person.cpp"
using namespace std;

void testLenText(){
    Person p;
    LengthTextBuffer Buff;
    Buff.Init(100);
    strcpy(p.LastName, "taware");
    strcpy(p.FirstName, "abhijit");
    strcpy(p.Address, "dange");
    strcpy(p.City, "pune");
    strcpy(p.State, "ma");
    strcpy(p.ZipCode, "33");
    p.Print(cout);
    Buff.Print(cout);
    cout << "pack person "<< p.Pack(Buff)<<endl;
    Buff.Print(cout);

    ofstream TestOut("lentext.dat", ios::out|ios::binary);
    Buff.Write(TestOut);
    Buff.Write(TestOut);
    strcpy(p.FirstName, "anaya");
    p.Print(cout);
    p.Pack(Buff);
    Buff.Print(cout);
    Buff.Write(TestOut);
    TestOut.close();

    Person p2;
    ifstream TestIn("lentext.dat", ios::in|ios::binary);
    cout << "read " << Buff.Read(TestIn) << endl;
    cout << "unpack " << p2.Unpack(Buff) << endl;
    p2.Print(cout);
}

int main(){
    testLenText();
    return 0;
}


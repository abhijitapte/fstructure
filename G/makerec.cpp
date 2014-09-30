#include<iostream>
#include"recordng.h"
#include"delim.h"
using namespace std;
//class DelimFieldBuffer;
class BufferFile;

int main(){
    int recaddr;
    DelimFieldBuffer Buffer;
    BufferFile RecordingFile(Buffer);
    RecordingFile.Create("record.dat", ios::out);
    Recording *R[10];
    R[0] = new Recording("LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel");

    for(int i=0; i<1; i++){
        R[i]->Pack(Buffer);
        recaddr = RecordingFile.Write();
        cout << "Recording R["<<i<<"] at recaddr "<<recaddr<<endl;
        delete R[i];
    }
    return 0;
}

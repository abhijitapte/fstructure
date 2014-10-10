#include<iostream>
using namespace std;
#include"recordng.h"

int main(){
    int recaddr;
    DelimFieldBuffer Buffer;
    DelimFieldBuffer::SetDefaultDelim('|');
    BufferFile RecordingFile(Buffer);
    RecordingFile.Create("record.dat", ios::out);
    Recording *R[10];
    R[0] = new Recording("LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel");
    R[1] = new Recording("LOF", "2313", "Someo Kuliet", "Qrokofiev", "Naazel");

    for(int i=0; i<2; i++){
        R[i]->Pack(Buffer);
        recaddr = RecordingFile.Write();
        cout << "Recording R["<<i<<"] at recaddr "<<recaddr<<endl;
        delete R[i];
    }
    return 0;
}

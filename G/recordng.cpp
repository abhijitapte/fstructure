#include<cstring>
#include<sstream>
#include"recordng.h"
using namespace std;

Recording::Recording(){
    IdNum[0] = 0; Title[0] = 0; Composer[0] = 0;
    Artist[0] = 0; Label[0] = 0;
}

Recording::Recording(char *label, char *idNum, char *title,
    char *composer, char *artist){
    strcpy(Label, label); strcpy(IdNum, idNum);
    strcpy(Title, title); strcpy(Composer, composer);
    strcpy(Artist, artist);
}

//char * Recording::Key() const{
string Recording::Key() const{
    ostringstream key;
    key << Label << IdNum << ends;
    return key.str();
}

int Recording::Pack(IOBuffer &Buffer) const{
    int numBytes;
    Buffer.Clear();
    numBytes = Buffer.Pack(IdNum);
    if(numBytes==-1) return -1;

    numBytes = Buffer.Pack(Title);
    if(numBytes==-1) return -1;

    numBytes = Buffer.Pack(Composer);
    if(numBytes==-1) return -1;

    numBytes = Buffer.Pack(Artist);
    if(numBytes==-1) return -1;

    numBytes = Buffer.Pack(Label);
    if(numBytes==-1) return -1;
    return 1;
}

int Recording::Unpack(IOBuffer &Buffer){
    int numBytes;
    numBytes = Buffer.Unpack(IdNum, 6);
    if(numBytes==-1) return -1;
    IdNum[numBytes]=0;

    numBytes = Buffer.Unpack(Title, 29);
    if(numBytes==-1) return -1;
    Title[numBytes]=0;

    numBytes = Buffer.Unpack(Composer, 29);
    if(numBytes==-1) return -1;
    Composer[numBytes]=0;

    numBytes = Buffer.Unpack(Artist, 29);
    if(numBytes==-1) return -1;
    Artist[numBytes]=0;

    numBytes = Buffer.Unpack(Label, 6);
    if(numBytes==-1) return -1;
    Label[numBytes]=0;

    return 1;
}

void Recording::Print(ostream &stream, char * label) const{
    stream << Label <<'|'<< IdNum <<'|'<< Title <<'|'
        << Composer <<'|'<< Artist;
}


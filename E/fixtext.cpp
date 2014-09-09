#include<string>
#include<cstring>
#include<iostream>
#include"fixtext.h"
using namespace std;

//construct with a maximum of maxFields.
FixedTextBuffer::FixedTextBuffer(int maxFields, int maxChars){
    Init(maxFields, maxChars);
}

//construct with a fields of specific size.
FixedTextBuffer::FixedTextBuffer(int numFields, int *fieldSize){
    Init(numFields, fieldSize);
}

int FixedTextBuffer::NumberOfFields() const{
    return NumFields;
}

void FixedTextBuffer::Clear(){
    NextField=0;
    NextCharacter=0;
    Packing=1;
    Buffer[0]=0;
}

int FixedTextBuffer::AddField(int fieldSize){
    if(NumFields==MaxFields) return 0;
    if(BufferSize + fieldSize > MaxChars) return 0;
    FieldSize[NumFields] = fieldSize;
    NumFields++;
    BufferSize += fieldSize;
    return 1;
}

void FixedTextBuffer::Init(int maxFields, int maxChars){
    if(maxFields<0) maxFields=0;
    if(maxChars<0) maxFields=0;
    MaxFields=maxFields;
    MaxChars=maxChars;
    FieldSize = new int[MaxFields];
    Buffer = new char[MaxChars];
    BufferSize=0;
    NumFields=0;
    NextField=0;
    Packing=1;
}

void FixedTextBuffer::Init(int numFields, int *fieldSize){
    int bufferSize = 1;
    for(int i=0; i< numFields; i++)
        bufferSize += fieldSize[i];

    Init(numFields, bufferSize);
    for(int j=0; j< numFields; j++)
        AddField(fieldSize[j]);
}

int FixedTextBuffer::Read(istream & stream){
    stream.read(Buffer, BufferSize);
    return stream.good();
}

int FixedTextBuffer::Write(ostream & stream) {
    stream.write(Buffer, BufferSize);
    return stream.good();
}

int FixedTextBuffer::Pack(const char *str){
    if(NextField==NumFields || !Packing) return 0;

    int len = strlen(str);
    int start = NextCharacter;
    int packSize = FieldSize[NextField];

    strncpy(&Buffer[start], str, packSize);
    NextCharacter += packSize;
    NextField++;

    //if len < packSize
    for(int i=start+len; i<NextCharacter; i++)
        Buffer[i] = ' ';
    Buffer[NextCharacter]=0;
    if(NextField==NumFields){
        Packing=0;
        NextField=NextCharacter=0;
    }
    return 1;
}

int FixedTextBuffer::Unpack(char *str){
    short len;
    if(NextField >= NumFields) return 0;
    //if(NextField >= NumFields||Packing) return 0;

    int start = NextCharacter;
    int packSize = FieldSize[NextField];

    strncpy(str, &Buffer[start], packSize);
    str[packSize]=0;
    NextCharacter += packSize;
    NextField++;
    if(NextField >= NumFields)  Clear();
    return 1;
}

void FixedTextBuffer::Print(ostream & stream) const{
    stream << "Buffer has max fields " << MaxFields
        << "\nand actual " << NumFields << endl
        << "max bytes " << MaxChars << " and buffer size "
        << BufferSize << endl;

    for(int i=0; i<NumFields; i++)
        stream << "\tfield " << i << " size " << FieldSize[i] << endl;

    if(Packing) stream << "\tPacking\n";
    else stream << "\tNot packing\n";
    stream << "Contents : " << Buffer << endl;
}

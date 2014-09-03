#include<string>
#include<cstring>
#include<iostream>
#include"lentext.h"
using namespace std;

//construct with a maximum of maxFields.
FixedTextBuffer::FixedTextBuffer(int maxFields, int maxChars){
    Init(maxFields, maxChars);
}

//construct with a fields of specific size.
FixedTextBuffer::FixedTextBuffer(int maxFields, int maxChars){
    Init(maxFields, maxChars);
}

void FixedTextBuffer::Clear(){
    NextBytes=0;
    BufferSize=0;
}

void FixedTextBuffer::Init(int maxBytes){
    if(maxBytes<0) maxBytes=0;
    MaxBytes = maxBytes;
    Buffer = new char[MaxBytes];
    Clear();
}

int FixedTextBuffer::Read(istream & stream){
    Clear();
    stream.read((char *)&BufferSize, sizeof(BufferSize));
    if(stream.fail()) return 0;
    if(BufferSize > MaxBytes) return 0;
    stream.read(Buffer, BufferSize);
    return stream.good();
}

int FixedTextBuffer::Write(ostream & stream) {
    stream.write((char*)(&BufferSize), sizeof(BufferSize));
    stream.write(Buffer, BufferSize);
    return stream.good();
}

int FixedTextBuffer::Pack(const char *str, short size){
    short len;

    if(size>=0) len=size;
    else len=strlen(str);

    if(len > strlen(str)) return 0;

    int start = NextBytes;
    NextBytes += (len + sizeof(len));
    if(NextBytes > MaxBytes) return 0;
    memcpy(&Buffer[start], &len, sizeof(len));
    strncpy(&Buffer[start+sizeof(len)], str, len);
    BufferSize = NextBytes;
    return 1;
}

int FixedTextBuffer::Unpack(char *str){
    short len;
    if(NextBytes >= BufferSize) return 0;

    int start = NextBytes;
    memcpy(&len, &Buffer[start], sizeof(len));
    NextBytes += (len + sizeof(len));
    if(NextBytes > BufferSize) return 0;
    strncpy(str, &Buffer[start+sizeof(len)], len);
    str[len]=0;
    return 1;
}

void FixedTextBuffer::Print(ostream & stream) const{
    stream << "Buffer has characters " << MaxBytes
        << "\nand Buffer size " << BufferSize << endl;
}



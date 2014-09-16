#include<string>
#include<cstring>
#include<iostream>
#include"length.h"
using namespace std;

LengthFieldBuffer::LengthFieldBuffer(int maxBytes)
    :VariableLengthBuffer(maxBytes){
    Init();
}

void LengthFieldBuffer::Clear(){
    VariableLengthBuffer::Clear();
}

int LengthFieldBuffer::Init(){
    Initialized = 1;
    Clear();
    return 1;
}

/*
int LengthFieldBuffer::ReadHeader(istream & stream){
    char ch;
    int result = VariableLengthBuffer::ReadHeader(stream);
    if(!result) return 0;
    stream.get(ch);
    if(!Initialized){
        SetDefaultLength(ch);
        return 1;
    }
    if(ch!=Length) return 0;
    return stream.tellg();
}

int LengthFieldBuffer::WriteHeader(ostream & stream) const{
    if(!Initialized) return 0;
    int result = VariableLengthBuffer::WriteHeader(stream);
    if(!result) return 0;
    stream.put(Length);
    return stream.tellp();
}
*/
int LengthFieldBuffer::Pack(const void *field, int size){
    short len;
    if(size>=0) len=size;
    else len=strlen((char*)field);

    int start = NextByte;
    NextByte += (len + sizeof(len));
    if(NextByte > MaxBytes) return -1;

    memcpy(&Buffer[start], &len, sizeof(len));
    memcpy(&Buffer[start+sizeof(len)], field, len);
    BufferSize = NextByte;
    return len;
}

int LengthFieldBuffer::Unpack(void *field, int maxBytes){
    int len=-1;
    if(NextByte >= BufferSize) return -1; // no more fields.

    int start = NextByte;
    memcpy(&len, &Buffer[start], sizeof(len));
    if(maxBytes!=-1 && len>maxBytes) return -1; //field too long.

    NextByte += len + sizeof(len);
    if(NextByte > BufferSize) return -1;
    memcpy(field, &Buffer[start+sizeof(len)], len);
    if(maxBytes > len || maxBytes==-1)
    ((char*)field)[len]=0;  //zero termination for string.
    return len;
}

void LengthFieldBuffer::Print(ostream & stream) const{
    VariableLengthBuffer::Print(stream);
}


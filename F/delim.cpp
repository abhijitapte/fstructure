#include<string>
#include<cstring>
#include<iostream>
#include"delim.h"
//#include"varlen.cpp"
using namespace std;

DelimFieldBuffer::DelimFieldBuffer(char delim, int maxBytes)
    :VariableLengthBuffer(maxBytes){
    Init(delim);
}

void DelimFieldBuffer::Clear(){
    VariableLengthBuffer::Clear();
}

void DelimFieldBuffer::Init(char delim){
    Initialized = 1;
    Clear();
    if(delim==-1) Delim = DefaultDelim;
    else Delim=delim;
    //Delim='|';
}

int DelimFieldBuffer::ReadHeader(istream & stream){
    char ch;
    int result = VariableLengthBuffer::ReadHeader(stream);
    if(!result) return 0;
    stream.get(ch);
    if(!Initialized){
        SetDefaultDelim(ch);
        return 1;
    }
    if(ch!=Delim) return 0;
    return stream.tellg();
}

int DelimFieldBuffer::WriteHeader(ostream & stream) const{
    if(!Initialized) return 0;
    int result = VariableLengthBuffer::WriteHeader(stream);
    if(!result) return 0;
    stream.put(Delim);
    return stream.tellp();
}

int DelimFieldBuffer::Pack(const void *field, int size){
    short len;

    if(size>=0) len=size;
    else len=strlen((char*)field);

    if(len > (short)strlen((char*)field)) return -1;

    int start = NextByte;
    NextByte += (len + 1);
    if(NextByte > MaxBytes) return -1;
    memcpy(&Buffer[start], field, len);
    Buffer[start+len] = Delim;
    BufferSize = NextByte;
    return len;
}

int DelimFieldBuffer::Unpack(void *field, int maxBytes){
    int len=-1;
    if(NextByte >= BufferSize) return -1;

    int start = NextByte;
    for(int i=start; i<BufferSize; i++){
        if(Buffer[i]==Delim){
            len = i - start;
            break;
        }
    }
    if(len==-1) return -1;
    NextByte += len + 1;
    if(NextByte > BufferSize) return -1;
    memcpy(field, &Buffer[start], len);
    if(maxBytes > len || maxBytes==-1)
    ((char*)field)[len]=0;
    return len;
}

void DelimFieldBuffer::Print(ostream & stream) const{
    VariableLengthBuffer::Print(stream);
    stream << "\nDelimiter :" << Delim << endl;
}

void DelimFieldBuffer::SetDefaultDelim(char delim){
    DefaultDelim = delim;
}

char DelimFieldBuffer::DefaultDelim = 0;


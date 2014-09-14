#include<iostream>
using namespace std;

IOBuffer::IOBuffer(int maxBytes){
    Init(maxBytes);
}

IOBuffer & IOBuffer::operator = (const IOBuffer & buffer){
    if(MaxBytes < buffer.BufferSize) return *this;
    Initialized = buffer.Initialized;
    BufferSize = buffer.BufferSize;
    memcpy(Buffer, buffer.Buffer, buffer.BufferSize);
    NextByte = buffer.NextByte;
    Packing = Packing
    return *this;
}

void IOBuffer::Clear(){
    NextByte = 0;
    Packing = 1;
}

void IOBuffer::Print(ostream & stream)const{
    stream<<"MaxBytes : "<<MaxBytes<<" BufferSize : "<<BufferSize<<endl;
}

void IOBuffer::Init(int maxBytes){
    Initialized = 0;
    if(MaxBytes < 0) maxBytes=0;
    MaxBytes = maxBytes;
    Buffer = new char[MaxBytes];
    BufferSize = 0;
    Clear();
    return 1;
}

int IOBuffer::DRead(istream & stream, int recref){
    stream.seekg(recref, ios::beg);
    if(stream.tellg() != recref) return -1;
    return Read(stream);
}

int IOBuffer::DWrite(ostream & stream, int recref) const{
    stream.seekp(recref, ios::beg);
    if(stream.tellp() != recref) return -1;
    return Write(stream);
}

static const char * headerStr = "IOBuffer";
static const int headerSize = strlen(headerStr);

int IOBuffer::ReadHeader(istream & stream){
    char str[9];
    stream.seekg(0, ios::beg);
    stream.read(str, headerSize);
    if(! stream.good()) return -1;
    if(strncmp(str, headerStr, headerSize)==0) return headerSize;
    else return -1;
}

int IOBuffer::WriteHeader(ostream & stream)const{
    stream.seekp(0, ios::beg);
    stream.write(headerStr, headerSize);
    if(! stream.good()) return -1;
    return headerSize;
}


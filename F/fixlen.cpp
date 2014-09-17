#include<iostream>
#include<cstring>
#include"fixlen.h"
using namespace std;

FixedLengthBuffer::FixedLengthBuffer(int recordSize)
    :IOBuffer(recordSize){
    Init(recordSize);
}

void FixedLengthBuffer::Clear(){
    IOBuffer::Clear();
    Buffer[0]=0;
    Packing=1;
}

int FixedLengthBuffer::Read(istream & stream){
    int recaddr = stream.tellg();
    stream.clear();
    Packing = 0;
    stream.read(Buffer, BufferSize);
    if(! stream.good()){
        stream.clear();
        return -1;
    }
    return recaddr;
}

int FixedLengthBuffer::Write(ostream & stream) const{
    int recaddr = stream.tellp();
    stream.write(Buffer, BufferSize);
    if(! stream.good()) return -1;
    return recaddr;
}

static const char * headerStr = "Fixed";
static const int headerSize = strlen(headerStr);

int FixedLengthBuffer::ReadHeader(istream & stream){
    char str[headerSize+1];
    int result, recordSize;
    result = IOBuffer::ReadHeader(stream);
    if(result<0) return -1;
    stream.read(str, headerSize);
    if(! stream.good()) return -1;
    if(strncmp(str, headerStr, headerSize)!=0) return -1;
    stream.read((char *)&recordSize, sizeof(recordSize));
    if(Initialized){
        if(recordSize != BufferSize) return -1;
    }
    ChangeRecordSize(recordSize);
    return stream.tellg();
}

/*
    Header consist of -
    IOBUFFER        Header
    FIXED           5 bytes
    record size     2 bytes
*/
int FixedLengthBuffer::WriteHeader(ostream & stream)const{
    int result;
    if(Initialized) return -1;
    result = IOBuffer::WriteHeader(stream);
    if(!result) return -1;
    stream.write(headerStr, headerSize);
    if(! stream.good()) return -1;
    stream.write((char *)&BufferSize, sizeof(BufferSize));
    if(! stream.good()) return -1;
    return stream.tellp();
}

void FixedLengthBuffer::Print(ostream &stream) const{
    IOBuffer::Print(stream);
    stream << "Fixed ";
}

int FixedLengthBuffer::Init(int recordSize){
    Clear();
    BufferSize = recordSize;
    return 1;
}

int FixedLengthBuffer::ChangeRecordSize(int recordSize){
    BufferSize = recordSize;
    return 1;
}

